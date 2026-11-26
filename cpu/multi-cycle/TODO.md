# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

## Completed Baseline

- Phase 2 base timing closed at **84 MHz** (`clk_cpu`) / **83.46 MHz** (`clk_vga`) after implementing the 0-cycle `eff_addr` bypass and evaluating and skipping `ALUOut`/`MDR` staging registers.

---

## Phase 2 M-Mode RTOS & Interrupt Enhancements (Target: >= 80–84 MHz)

Additions below keep M-mode-only simplicity (no S-mode/U-mode or MMU) while isolating combinational paths behind registered MMIO (`io_dout`) and `STATE_FETCH` sampling so `clk_cpu` stays comfortably >= 80 MHz (aiming to preserve 84 MHz).

### Priority 3 — `WFI` Instruction (`FUNCT12_WFI = 12'h105`)
- Decode `WFI` under `OPC_SYSTEM` in `control_fsm.sv` into a `STATE_WFI` state that stalls until an interrupt is pending, allowing the RTOS idle task to halt cleanly instead of spinning.

### Optional / Stretch (or Phase 3) — Simple MMIO SPI Master (`0x2000_00xx`)
- Decoupled ~10–25 MHz SPI controller behind `io_dout` for an SD Card PMOD or onboard Arty A7 QSPI Flash (`FatFs`/`LittleFS` persistent storage and dynamic app loading).

### Explicitly Deferred (Phase 3 / Phase 4)
- Lower-8 KB bootloader write protection (`0x0000_0000–0x0000_1FFF`) — deferred to Phase 3 memory architecture redesign.
- DDR3 MIG external memory, PMP (`pmpcfg*`/`pmpaddr*`), S-mode/U-mode, and Sv39 MMU remain deferred to Phase 3/4.
