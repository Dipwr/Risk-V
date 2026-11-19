# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

## 1. Architectural & Timing Bottlenecks (Fmax ~25 MHz)

- [ ] **1.3 [Deferred] Re-evaluate `ALUOut` / `MDR` Memory Staging Registers (`datapath.sv`, `control_fsm.sv`)**
  - **Files:** `datapath.sv:62`, `datapath.sv:121-172`, `control_fsm.sv:203-225`, `soc_top.sv:34-55`
  - **Notes:** Deferred until post-**1.2** Vivado `report_timing_summary` results are checked:
    - **`MDR` (skip unless pipelining `FETCH` too):** `STATE_DECODE` already shares the same BRAM read mux + cross-die routing path without a staging register, so adding `MDR` (+1 cycle per `LOAD`) only trims ~1–2 ns of local byte/sign-extend muxing while `STATE_DECODE` remains at nearly the same Fmax ceiling.
    - **`ALUOut` (conditional on timing):** Adds +1 cycle to both `STORE` (3->4) and `LOAD` (4->5), costing ~9% average CPI; only worth adding if Vivado timing shows `STATE_LOAD_REQ`/`STATE_STORE` (`u_alu -> mem_addr/mem_wbe -> 128 BRAMs`) trailing `STATE_DECODE` by >10–15%.

---

## 3. SoC, Peripherals, & FPGA Hardware Issues

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
