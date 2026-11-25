# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

## Completed Baseline

- Phase 2 base timing closed at **84 MHz** (`clk_cpu`) / **83.46 MHz** (`clk_vga`) after implementing the 0-cycle `eff_addr` bypass and evaluating and skipping `ALUOut`/`MDR` staging registers.

---

## Phase 2 M-Mode RTOS & Interrupt Enhancements (Target: >= 80–84 MHz)

Additions below keep M-mode-only simplicity (no S-mode/U-mode or MMU) while isolating combinational paths behind registered MMIO (`io_dout`) and `STATE_FETCH` sampling so `clk_cpu` stays comfortably >= 80 MHz (aiming to preserve 84 MHz).

### Priority 1 — CLINT-Style MMIO Timer (`mtime`/`mtimecmp`) & Machine Timer Interrupt (`MTI`)
- Add 64-bit `mtime` and `mtimecmp` memory-mapped registers in `soc_top.sv` (`is_io`, `0x2000_00xx`) behind the existing 1-cycle registered `io_dout` read path.
- Register the comparator output (`timer_irq_q <= (mtime >= mtimecmp);`) inside the timer peripheral to isolate the 64-bit carry chain from CPU control/datapath STA.
- Add `CSR_MIE` (`0x304`: `MTIE`/`MEIE`) and `CSR_MIP` (`0x344`: `MTIP`/`MEIP`) in `csr_unit.sv`, and wire `CSR_TIME`/`CSR_TIMEH` to mirror `mtime`.
- Sample a single registered `irq_take` signal **only at `STATE_FETCH`** in `control_fsm.sv` (leaving `STATE_DECODE`, ALU, and memory critical paths untouched), reusing `STATE_TRAP` with `mcause = 32'h8000_0007`.
- Configure `configMTIME_BASE_ADDRESS`, `configMTIMECMP_BASE_ADDRESS`, and `configUSE_PREEMPTION = 1` / `configUSE_TIME_SLICING = 1` in `Programs/freertos_demo/FreeRTOSConfig.h` to unlock preemptive FreeRTOS (`vTaskDelay()`, blocking timeouts, software timers).

### Priority 2 — External Interrupt Mux (`MEI`) for UART RX & VGA VBlank
- Add a small MMIO interrupt enable/pending register in `soc_top.sv` combining already-registered `uart_rx_avail` and edge-latched `vblank_sync_2` (W1C) -> `MEIP` (`mcause = 32'h8000_000B`).
- Replaces busy-polling loops in RTOS tasks with interrupt-driven UART RX queues and VBlank semaphores; negligible LUT/timing impact.

### Priority 3 — `WFI` Instruction (`FUNCT12_WFI = 12'h105`)
- Decode `WFI` under `OPC_SYSTEM` in `control_fsm.sv` into a `STATE_WFI` state that stalls until an interrupt is pending, allowing the RTOS idle task to halt cleanly instead of spinning.

### Priority 4 — Lower-8 KB Bootloader Write Protection (`0x0000_0000–0x0000_1FFF`)
- Mask BRAM write-enable in `soc_top.sv` when `mem_addr[17:13] == 5'd0` (and optionally raise `CAUSE_STORE_ACCESS_FAULT` = `7` in `STATE_STORE` alongside `store_misaligned`) so runaway M-mode tasks cannot corrupt `uart_boot`.

### Priority 5 — MMIO Software Reset / Watchdog Register
- Add a small MMIO control/countdown register in `soc_top.sv` asserting a clean synchronous `rst_cpu` pulse for software reboot / hang recovery without pressing `BTN0`.

### Optional / Stretch (or Phase 3) — Simple MMIO SPI Master (`0x2000_00xx`)
- Decoupled ~10–25 MHz SPI controller behind `io_dout` for an SD Card PMOD or onboard Arty A7 QSPI Flash (`FatFs`/`LittleFS` persistent storage and dynamic app loading).

### Explicitly Deferred (Phase 3 / Phase 4)
- DDR3 MIG external memory, PMP (`pmpcfg*`/`pmpaddr*`), S-mode/U-mode, and Sv39 MMU remain deferred to Phase 3/4.
