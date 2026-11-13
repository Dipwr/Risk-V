# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

## 1. Architectural & Timing Bottlenecks (Fmax ~25 MHz)

- [ ] **1.2 Pipeline / Multi-Cycle the 33x33 Multiplier (`alu.sv`, `control_fsm.sv`)**
  - **Files:** `alu.sv:14-33`, `alu.sv:55-58`
  - **Issue:** `assign mul_prod = mul_a * mul_b;` cascades 4 `DSP48E1` slices completely combinationally (`AREG=0, BREG=0, MREG=0, PREG=0`) from `alu_op` decode through `rf_wdata` writeback in a single `STATE_EXECUTE` cycle (~15–20+ ns delay).
  - **Goal:** Split multiplication across 2–3 clock cycles (or a dedicated multiply state/pipeline) with synchronous registers so Vivado packs `AREG`/`BREG`, `MREG`, and `PREG` inside the `DSP48E1` slices.

- [ ] **1.3 Add `ALUOut` and `MDR` Staging Registers on the Memory Path (`datapath.sv`, `control_fsm.sv`)**
  - **Files:** `datapath.sv:56`, `datapath.sv:118-169`, `control_fsm.sv:187-209`, `soc_top.sv:33-55`
  - **Issue (Address/Control Path):** In `STATE_STORE` and `STATE_LOAD_REQ`, `mem_addr` is driven directly by the combinational `alu_result` (and `mem_wbe` is shifted by `mem_addr[1:0]`), which then fans out across the entire FPGA die to **128 `RAMB36E1` blocks** (95% of the Arty A7-100T's BRAMs).
  - **Issue (Read Data Path):** In `STATE_LOAD_WB`, `mem_rdata` travels from the 64-BRAM mux tree through the byte/halfword shifter and sign extender directly into the register file write port without an `MDR` register.
  - **Goal:** Register the computed effective address (`alu_out`) before driving the BRAM bus, and/or register the incoming memory read data (`mdr`) before byte extraction and register file writeback.

- [ ] **1.4 Remove Asynchronous Reset Loop on Register File Array to Infer `RAM32M` LUTRAM (`regfile.sv`)**
  - **Files:** `regfile.sv:20-28`
  - **Issue:** Resetting all 32 words of `regdata` in `if (rst)` prevents Vivado from inferring Distributed RAM (`RAM32M`) or BRAM, forcing synthesis into **1,024 Flip-Flops (`FDCE`)** plus large 32-to-1 LUT multiplexer trees.
  - **Goal:** Remove the hardware reset loop on `regdata` (keeping `x0` hardwired to `0` on reads) so Vivado synthesizes the register file into 12 `RAM32M` primitives (48 LUTs).

- [ ] **1.5 Evaluate Branch Comparator Resource Sharing (`datapath.sv`)**
  - **Files:** `datapath.sv:74-85`
  - **Issue:** `pc + imm` and `pc + 4` now reuse `u_alu`, leaving only the separate 32-bit `branch_taken` comparator (which currently runs in parallel with `u_alu`'s `pc + imm` calculation during `STATE_IMM_PC` so branches complete in 3 cycles).

---

## 2. Functional & ISA Implementation Bugs

- [ ] **2.2 Implement Multi-Cycle Sequential Divider for RV32M (`DIV`, `DIVU`, `REM`, `REMU`) (`alu.sv`, `control_fsm.sv`, `datapath.sv`)**
  - **Files:** `alu.sv:60-88`, `Programs/compiler/build.sh:84`
  - **Issue:** `ALU_DIV`, `ALU_DIVU`, `ALU_REM`, and `ALU_REMU` are currently stubbed to return `32'd0` because combinational `/` and `%` cannot meet FPGA timing, while `build.sh` compiles with `-march=rv32im`.
  - **Goal:** Implement a sequential iterative divider (e.g., 32-cycle restoring/non-restoring divider) outside the combinational ALU path, controlled by a `STATE_DIV` state in `control_fsm` that waits for `div_done` (remembering RISC-V corner cases: divide-by-zero and signed overflow `-2^31 / -1`).

- [ ] **2.3 Connect `RESET_PC` Parameter to `datapath` (`rv32_core.sv`, `datapath.sv`)**
  - **Files:** `rv32_core.sv:3-5`, `rv32_core.sv:68`, `datapath.sv:3`, `datapath.sv:88-91`
  - **Issue:** `rv32_core` declares `parameter logic [31:0] RESET_PC = 32'h0000_0000`, but never passes it to `u_datapath`, which hardcodes `pc <= 32'h00000000;`.

- [ ] **2.4 Check Halfword Load/Store Offset Shifting (`datapath.sv`)**
  - **Files:** `datapath.sv:122`, `datapath.sv:147-150`
  - **Issue:** `LH`/`LHU` and `SH` only use `load_byte_offset[1]` / `mem_addr[1]` instead of the full 2-bit offset.

---

## 3. SoC, Peripherals, & FPGA Hardware Issues

- [ ] **3.1 Fix UART Receiver Shift Register Overwrite & Stop-Bit Framing Check (`uart.sv`, `soc_top.sv`)**
  - **Files:** `uart.sv:78-100`, `soc_top.sv:71-87`
  - **Issue 1 (Data corruption):** `RX_DATA` shifts incoming bits directly into `rx_data_reg`, which is also the register read by the CPU. If a second byte starts arriving before the CPU reads the first byte, `rx_data_reg` is corrupted mid-reception. Use a separate `rx_shift_reg` and latch into `rx_data_reg` only in `RX_STOP`.
  - **Issue 2 (Framing / break bug):** `RX_STOP` transitions to `RX_IDLE` at the middle of the stop bit and sets `rx_ready <= 1'b1` without checking `rx_sync_2 == 1'b1`. A low line (break condition or framing error) immediately re-triggers a false start bit in `RX_IDLE`.
  - **Issue 3 (Partial address decode):** `u_uart` only checks `addr[3:0] == 4'h0` while `soc_top` asserts `uart_we`/`uart_re` for all of `is_io`, causing aliases every 16 bytes (`0x2000_0010`, `0x2000_0020`, etc.).

- [ ] **3.2 Add Reset Synchronizers & Convert to Synchronous Resets for Xilinx 7-Series (`arty_a7_top.sv`, all `.sv` modules)**
  - **Files:** `arty_a7_top.sv:17-45`, all sequential `always_ff` blocks
  - **Issue 1 (Metastability on reset release):** `sys_rst = rst || !clk_locked;` combines an unsynchronized button (`btn_rst`) with `!clk_locked` and drives asynchronous resets (`posedge rst`) in both `clk_cpu` and `clk_vga` domains without synchronizing deassertion to either clock.
  - **Issue 2 (DSP/BRAM packing):** Using `always_ff @(posedge clk or posedge rst)` prevents Vivado from packing registers into `DSP48E1` and `RAMB36E1` primitives (which only support synchronous resets).

- [ ] **3.3 Optimize VGA Controller Address Generation & Register RGB Outputs (`vga_controller.sv`)**
  - **Files:** `vga_controller.sv:74-93`, `vga_controller.sv:101-125`
  - **Issue 1 (Redundant 16-bit adder at 83.46 MHz):** `assign vram_addr = (page_sync_2 ? 16'd32768 : 16'd0) + (pixel_index >> 1);` infers a second 16-bit carry-chain adder in series with `pixel_index` before fanning out to 64 VRAM blocks. Since `pixel_index >> 1` is `< 32768`, this can be replaced with `{page_sync_2, pixel_index[15:1]}` (0 LUTs).
  - **Issue 2 (Unregistered RGB outputs):** `vga_r`, `vga_g`, and `vga_b` are driven combinationally from the 64-BRAM read mux while `vga_hs` and `vga_vs` are registered. Registering `vga_r/g/b` (and matching `vga_hs/vs` latency) allows `IOB` pad register packing and cleaner 83.46 MHz timing.

- [ ] **3.4 Update `syscalls.c` to Match the Multi-Cycle SoC Memory Map (`Programs/compiler/syscalls.c`)**
  - **Files:** `Programs/compiler/syscalls.c:10-12`, `syscalls.c:19-30`, `syscalls.c:48`, `syscalls.c:85`
  - **Issue:** `syscalls.c` still uses the Stage-1 single-cycle MMIO addresses (`0x00080004`, `0x00080020`, `0x00080024`, `0x00080000`) and `STACK_LIMIT` (`0x00078000`), and `_write()` does not poll UART TX ready (`*UART_STAT & 2`) before sending each byte.
