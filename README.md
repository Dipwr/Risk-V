# Risk-V: RV32IM Processor & SoC Architecture

A custom **RISC-V (RV32IM)** processor implementation developed from fundamental digital logic schematics to a synthesizable multi-cycle SystemVerilog SoC targeted for FPGA silicon.

---

## 📌 Project Overview & Goals

The primary goal of **Risk-V** is to build a complete, self-contained RISC-V computing system from scratch:
1. **Instruction Set Architecture**: Full compliance with the unprivileged **RV32I** Base Integer ISA and the **RV32M** Standard Extension for Integer Multiplication and Division.
2. **Four-Phase Evolutionary Roadmap**:
   - **Phase 1 (Single-Cycle & Simulation Platform)**: Educational schematic capture in [Digital](https://github.com/hneemann/Digital), Verilog export, and high-performance cycle-accurate simulation in **Verilator + SDL2** with a rich bare-metal software ecosystem.
   - **Phase 2 (Multi-Cycle Synthesizable Core & FPGA SoC)**: Modular **SystemVerilog** rewrite optimized for physical FPGA hardware (**Digilent Arty A7-100T**), featuring hardware BRAM, dual-port VRAM, tear-free hardware VGA pixel generation (1280x800 @ 60 Hz with 4x hardware upscaling and selectable VSync), pipelined DSP48E1 multiply / sequential divide units, a FIFO-buffered UART controller, and a cross-platform Verilator + SDL2 + PTY simulator (`cpu/multi-cycle/sim/`).
   - **Phase 3 (RV32IM 5-Stage Pipelined Core)**: Pipelined SystemVerilog microarchitecture (`IF/ID`, `ID/EX`, `EX/MEM`, `MEM/WB`) with RAW/load-use hazard detection, EX/MEM & MEM/WB forwarding paths, and branch control-hazard resolution.
   - **Phase 4 (RV64 Core, Virtual Memory & Linux Boot)**: `XLEN=64` datapath scaling (`ADDW`/`SUBW`/`SLLW`/`LD`/`SD`), M-Mode/S-Mode CSRs and trap delegation, Sv39 3-level hardware Page Table Walker & TLB MMU, and OpenSBI + Device Tree + Linux kernel boot.
3. **Full-Stack Bare-Metal Software**:
   - Adapted **Wozmon-style** interactive monitor and hex program loader in RISC-V assembly.
   - Multi-target bare-metal BSP/HAL + Newlib-nano C runtime (`Programs/bsp/`, `Programs/lib/syscalls.c`).
   - Hardware-agnostic test & demo suite (`Programs/apps/`): RV32IM architectural test suite, 3D wireframe graphics engine, fluid dynamics solver, Mandelbrot renderer, Conway's Game of Life, and physics benchmarks.

---

## 🏛️ System Architecture

### 1. Phase 1: Single-Cycle Simulator Architecture
- **Design Tool**: HNeemann's *Digital* logic simulator (`.dig` files) exported to Verilog (`main_cpu.v`).
- **Execution Model**: Single-cycle datapath with sequential multi-cycle math submodules (hardware multiplier and sequential restoring divider).
- **Simulation**: Verilator C++ testbench (`sim_main.cpp`) linked against **SDL2**.
- **Display**: 320x200 16-bit RGB565 double-buffered display scaled 3x in windowed SDL2, with a real-time status banner reporting execution frequency (MHz) and cycle count.
- **I/O**: Keyboard FIFO buffer, mouse coordinates/buttons, and terminal stdout MMIO.

```
+-------------------------------------------------------------------------+
|                              Phase 1 Memory Map                         |
+-------------------------------------------------------------------------+
| Region              | Base Address | End Address  | Size   | Notes      |
+---------------------+--------------+--------------+--------+------------+
| Boot ROM            | 0x0000_0000  | 0x0003_FFFF  | 256 KB | Wozmon     |
| Unified RAM         | 0x0004_0000  | 0x0007_FFFF  | 256 KB | Code/Stack |
| Standard MMIO       | 0x0008_0000  | 0x0008_1FFF  | 8 KB   | I/O Regs   |
|   PAGE_REG          | 0x0008_0000  |              | 4 B    | Page Flip  |
|   TERM_OUT          | 0x0008_0004  |              | 4 B    | UART Out   |
|   KEY_DATA          | 0x0008_0020  |              | 4 B    | Key FIFO   |
|   KEY_STAT          | 0x0008_0024  |              | 4 B    | Key Ready  |
|   MOUSE_X / Y / BTN | 0x0008_0028  | 0x0008_0030  | 12 B   | Mouse MMIO |
| Graphics Page 0     | 0x0008_2000  | 0x000A_13FF  | 128 KB | RGB565 FB  |
| Graphics Page 1     | 0x000A_1400  | 0x000C_07FF  | 128 KB | RGB565 FB  |
+---------------------+--------------+--------------+--------+------------+
```

---

### 2. Phase 2: Multi-Cycle FPGA SoC Architecture
- **Target Hardware**: Digilent Arty A7-100T (Xilinx Artix-7 `XC7A100T`, 135 BRAMs — required for 512 KB total on-chip RAM + VRAM).
- **Core RTL**: Written in modular SystemVerilog (`cpu/multi-cycle/core/`) using synchronous resets across all sequential logic for Xilinx 7-series primitive packing (`DSP48E1`, `RAMB36E1`, `RAM32M`/`RAM64M`).
- **Clock Domains & Reset Architecture**:
  - `clk_cpu` (parameterized `CPU_CLK_FREQ`, default `25 MHz`): Core logic, BRAM, UART, MMIO.
  - `clk_vga` (`83.46 MHz`): VESA 1280x800 @ 60 Hz CVT pixel clock.
  - Generated via Xilinx Clocking Wizard (`clk_wiz_0`) from the onboard 100 MHz oscillator (`CLK100MHZ`), kept continuously running (`.reset(1'b0)`) so `BTN0` never stops or glitches clocks.
  - Per-domain async-assert / sync-deassert reset synchronizers (`rst_cpu`, `rst_vga`) in `arty_a7_top.sv` driven by `btn_rst || !clk_locked`.
- **Memory & Video Subsystem**:
  - **Main RAM** (`bram_ram.sv`): 256 KB Block RAM initialized with boot payload (`BOOT_HEX`, default `"boot.mem"`).
  - **Dual-Port VRAM** (`vram.sv`): 256 KB true dual-port RAM holding two 128 KB 320x200 RGB565 framebuffers (Port A: CPU R/W, Port B: VGA Rasterizer).
  - **Hardware VGA Controller** (`vga_controller.sv`): Multiplier-free address generator (`(y << 8) + (y << 6) + x`) with zero-LUT page concatenation (`{active_page, pixel_index[15:1]}`), VBlank page latching with software-selectable VSync bypass (`no_vsync` bit for immediate uncapped flips), synchronized `vblank` and `active_page` status outputs back to `clk_cpu`, 4x hardware pixel upscaling (320x200 -> 1280x800), and 2-stage registered `vga_r/g/b` + `vga_hs/vs` outputs for IOB packing.
  - **UART Controller** (`uart.sv`): Parameterized `CLK_FREQ`/`BAUD` (default 115200 8N1), 64-byte LUTRAM-inferred RX and TX circular FIFOs, isolated RX shift register, stop-bit framing check and line-break recovery (`RX_WAIT_IDLE`), `ASYNC_REG` 2-FF RX synchronizer, sticky W1C error flags (`rx_overrun`, `rx_framing_err`), RX FIFO flush, and `tx_idle` status.

```
+------------------------------------------------------------------------------+
|                              Phase 2 Memory Map                              |
+------------------------------------------------------------------------------+
| Region               | Base Address | End Address  | Size   | Notes          |
+----------------------+--------------+--------------+--------+----------------+
| System RAM (BRAM)    | 0x0000_0000  | 0x0003_FFFF  | 256 KB | Boot/Code      |
|   Wozmon Monitor     | 0x0000_0000  | 0x0000_FFFF  | 64 KB  | Bootloader     |
|   User Program Area  | 0x0001_0000  | 0x0003_FFFF  | 192 KB | Apps/Stack     |
| Video RAM (VRAM)     | 0x1000_0000  | 0x1003_FFFF  | 256 KB | Dual-Port      |
|   Framebuffer Page 0 | 0x1000_0000  | 0x1001_FFFF  | 128 KB | 320x200 RGB565 |
|   Framebuffer Page 1 | 0x1002_0000  | 0x1003_FFFF  | 128 KB | 320x200 RGB565 |
| Peripheral MMIO      | 0x2000_0000  | 0x2000_00FF  | 256 B  | Strict Decode  |
|   UART Data (TX/RX)  | 0x2000_0000  |              | 4 B    | R: RX pop / W: TX push |
|   UART Status / Ctrl | 0x2000_0004  |              | 4 B    | R:[0]rx_rdy [1]tx_rdy [2]ovr [3]frm [4]tx_idle |
|                      |              |              |        | W:[2]clr_ovr [3]clr_frm [4]rx_flush |
|   VGA Page / VSync   | 0x2000_0008  |              | 4 B    | W:[0]page [1]no_vsync; R:[0]page [1]vblank [2]active_page [3]no_vsync |
+----------------------+--------------+--------------+--------+----------------+
```

---

## ⚙️ Microarchitecture & FSM

The multi-cycle core (`rv32_core.sv`) decouples control (`control_fsm.sv`) from the datapath (`datapath.sv`), with `RESET_PC` propagated as a top-level synthesis parameter and registered `ir` severed from live `mem_rdata` to eliminate static timing false paths:

```
                              +-------------------+
                              |    STATE_RESET    |
                              +-------------------+
                                        |
                                        v
                              +-------------------+
        +-------------------->|    STATE_FETCH    |
        |                     +-------------------+
        |                               |
        |                               v
        |                     +-------------------+
        |                     |   STATE_DECODE    |
        |                     +-------------------+
        |        /      /      /      |       \       \         \
        |       v      v      v       v        v       v         v
        |  +--------+ +----+ +-----+ +-------+ +----+ +-----+ +--------------+
        |  |STATE_  | |EX  | |STATE| |STATE_ | |JALR| |STORE| |STATE_LOAD_REQ|
        |  |IMM_PC  | |    | |_MUL | |DIV    | |    | |     | +--------------+
        |  +--------+ +----+ +-----+ +-------+ +----+ +-----+        |
        |      |        |     (5 cyc) (2/34c)    |       |           v
        |      |        |       |        |       |       |    +--------------+
        |      |        |       |        |       |       |    |STATE_LOAD_WB |
        |      |        |       |        |       |       |    +--------------+
        |      \________|_______|________|_______|_______|___________/
        +--------------------------------+
```

- **Instruction Fetch (`STATE_FETCH`)**: Asserts `mem_req` with `mem_addr = pc`.
- **Instruction Decode & Register Fetch (`STATE_DECODE`)**: Latches `ir <= mem_rdata`, reads `regfile` (`RAM32M`, no runtime reset) into `reg_a`/`reg_b`, computes `pc_4 = pc + 4` via `u_alu`, and selects the next FSM state from live `dec_opcode`/`dec_funct3`/`dec_funct7`.
- **PC-Relative / Upper-Immediate / Branch (`STATE_IMM_PC`)**: Completes `BRANCH` (using 3 shared base comparators for `BEQ`/`BNE`/`BLT`/`BGE`/`BLTU`/`BGEU`), `JAL`, `LUI`, `AUIPC`, and unimplemented/NOP opcodes.
- **Execute (`STATE_EXECUTE`)**: Single-cycle RV32I ALU operations (`alu.sv`, 10 ops).
- **Multiply (`STATE_MUL`)**: Dedicated `mul_unit.sv` — 4-stage `en`-gated `DSP48E1` pipeline (`a_ext_q`/`b_ext_q` + `s1..s3_prod`), completing `MUL`/`MULH`/`MULHSU`/`MULHU` in 5 cycles in `STATE_MUL` (7 cycles total).
- **Divide (`STATE_DIV`)**: Dedicated `div_unit.sv` — 32-step restoring binary divider with a shared post-negator and 2-cycle fast-paths for divide-by-zero and signed `-2^31 / -1` overflow (34 cycles normal in `STATE_DIV`).
- **Memory Access (`STATE_STORE`, `STATE_LOAD_REQ` -> `STATE_LOAD_WB`)**: Single-cycle request for stores, two-cycle request/writeback for loads to match synchronous BRAM read latency.

---

## 💻 Software & Ecosystem

### 1. Wozmon Interactive Bootloader
Ported to RV32I assembly (`Programs/bootloaders/multi_cycle/visual_wozmon320x200.s` for Phase 2, and `Programs/bootloaders/single_cycle/` for Phase 1). Runs on power-up and provides an interactive terminal over UART and on-screen framebuffer:
- Inspect memory addresses: `<addr>` (e.g. `10000`).
- Examine memory ranges: `<start>.<end>`.
- Deposit data bytes: `<addr>: <val1> <val2> ...`.
- Execute user programs: `<addr> R` (e.g. `10000 R`).

### 2. Multi-Target BSP & Bare-Metal C Toolchain
- **Compiler**: Standard RISC-V GCC toolchain (`riscv-none-elf-gcc`, `riscv64-unknown-elf-gcc`, etc.) with flags `-march=rv32im -mabi=ilp32 -O2`.
- **Target BSPs (`Programs/bsp/`)**:
  - `bsp/include/bsp.h`: Unified HAL API (`bsp_vram_page`, `bsp_set_page`, `bsp_set_vsync`, `bsp_vblank`, `bsp_active_page`, `bsp_wait_vblank`, `bsp_present_page`, `bsp_putc`, `bsp_puts`, `bsp_key_avail`, `bsp_getc`, `bsp_try_getc`, `bsp_exit`) abstracting memory maps, VRAM page strides (`64000` vs `65536` pixels), VSync/active-page handoff, and console/UART I/O.
  - `bsp/single_cycle/`: Phase 1 target (`0x0004_0000` RAM, `0x0008_2000` VRAM, `TERM_OUT`/`KEY_*` MMIO, Wozmon load `40000`).
  - `bsp/multi_cycle/`: Phase 2 target (`0x0001_0000` RAM, `0x1000_0000` VRAM, polling UART + VBlank `PAGE_REG`, Wozmon load `10000`).
- **Syscalls**: Target-agnostic Newlib-nano bridge (`Programs/lib/syscalls.c`) delegating `_write`, `_read`, `_sbrk`, and `_exit` to the active BSP HAL and linker symbols (`_end`, `_heap_limit`).
- **Automation**: `Programs/build.sh` compiles for either `multi_cycle` (default) or `single_cycle`, emits artifacts under `Programs/out/<target>/<app>/`, generates Wozmon hex payloads via `Programs/tools/bin2hex.py`, and copies the payload to the clipboard via `Programs/tools/paste.py` (with `Programs/tools/serialpaste.py` for UART upload).

### 3. Application & Test Suite (`Programs/apps/`)
All applications build against both `single_cycle` and `multi_cycle` targets via `bsp.h`:
- `test_suite`: RV32IM architectural verification suite (102 base + multiply tests; optional divider tests).
- `wireframe`: 3D matrix rotation & Bresenham wireframe renderer with live VSync ON/OFF toggle (`v`) (models in `Programs/assets/3d/`).
- `fluid_sim`: 2D Eulerian wind tunnel & pressure fluid solver.
- `mandelbrot`: Fixed-point Mandelbrot fractal explorer with cosine palettes.
- `GoL`: Conway's Game of Life.
- `bounce_sim`: Multi-ball Q16.16 physics simulation.
- `dvd_bounce`: Double-buffered bouncing box test.
- `profiler_workload`: PGO and simulator benchmark combining 3D rotation and procedural rendering.

---

## 📁 Repository Layout

```
Risk-V/
├── README.md                      # Project documentation (this file)
├── AGENTS.md                      # Workspace rules & RTL/verification guidelines
├── cpu/
│   ├── riscv-unprivileged.pdf     # RISC-V specification reference
│   ├── riscv-opcodes.pdf          # Instruction encoding reference
│   ├── single-cycle/              # Phase 1: Single-Cycle Core
│   │   ├── cpu_guide.txt          # Bare-metal programmer's reference guide
│   │   ├── digital/               # Digital logic schematics (.dig files)
│   │   └── verilog/               # Verilog export & Verilator SDL2 testbench
│   └── multi-cycle/               # Phase 2: Multi-Cycle FPGA Core
│       ├── TODO.md                # Active architectural, timing & Zicsr backlog
│       ├── core/                  # SystemVerilog RTL implementation
│       │   ├── rv32_pkg.sv        # Package with opcodes, funct3/7, ALU & FSM types
│       │   ├── rv32_core.sv       # CPU core top (links FSM & Datapath)
│       │   ├── control_fsm.sv     # Multi-cycle control state machine
│       │   ├── datapath.sv        # Register file, ALU/MUL/DIV, imm gen, PC logic
│       │   ├── regfile.sv         # 32 x 32-bit LUTRAM-inferred register file
│       │   ├── alu.sv             # RV32I 10-op combinational ALU
│       │   ├── mul_unit.sv        # 4-stage en-gated DSP48E1 RV32M multiplier
│       │   ├── div_unit.sv        # 32-step restoring RV32M divider
│       │   ├── imm_gen.sv         # Immediate decoder (I, S, B, U, J types)
│       │   ├── soc_top.sv         # SoC interconnect, BRAM, VRAM, MMIO & CDC
│       │   ├── bram_ram.sv        # 256 KB internal program Block RAM
│       │   ├── vram.sv            # 256 KB dual-port video RAM
│       │   ├── vga_controller.sv  # 1280x800 @ 60Hz tear-free 4x upscaled VGA
│       │   ├── uart.sv            # Hardware UART (64B RX/TX FIFOs, error flags)
│       │   └── arty_a7_top.sv     # Top-level wrapper & reset sync for Arty A7-100T
│       └── sim/                   # Verilator + SDL2 + PTY simulator for arty_a7_top
│           ├── clk_wiz_0.sv       # Behavioral MMCM stub for Verilator
│           ├── sim.vlt            # Verilator config exposing clock/RAM/VRAM hooks
│           ├── gen_boot_mem.py    # Converts Wozmon .bin to 65536-word boot.mem
│           ├── sim_main.cpp       # SDL2 + bit-accurate UART PTY + dual-mode VGA harness
│           └── Makefile           # Build, lint, PGO, and run targets
└── Programs/
    ├── build.sh                   # Multi-target build script (./build.sh <target> <app>)
    ├── bsp/
    │   ├── include/bsp.h          # Unified Hardware Abstraction Layer header
    │   ├── single_cycle/          # Phase 1 target (linker.ld, boot.s, hal.c, target.env)
    │   └── multi_cycle/           # Phase 2 target (linker.ld, boot.s, hal.c, target.env)
    ├── lib/
    │   └── syscalls.c             # Target-agnostic Newlib-nano syscall bridge
    ├── apps/                      # Hardware-agnostic bare-metal tests & demos
    ├── bootloaders/               # Wozmon bootloaders (single_cycle, multi_cycle) & asm demos
    ├── assets/3d/                 # 3D models (OBJ) and C array converter
    └── tools/                     # bin2hex.py, paste.py, serialpaste.py, rv32i_to_intel_hex.py
```

---

## 🚀 Quick Start Guide

### 1. Running the Phase 1 Verilator Simulation
Ensure prerequisites are installed: `verilator`, `libsdl2-dev`, and `make`.

```bash
cd cpu/single-cycle/verilog
make -j$(nproc)
make run
```
To run with Profile-Guided Optimization (PGO) for maximum simulation speed:
```bash
make pgo-gen
make run        # Run simulation for ~15 seconds to collect profile data, then close window
make pgo-use
make run
```

### 2. Building Bare-Metal C Programs
Ensure a RISC-V GCC toolchain (e.g. `riscv-none-elf-gcc`) and Python 3 are in your `PATH`.

```bash
cd Programs
./build.sh multi_cycle dvd_bounce     # Build for Phase 2 Multi-Cycle FPGA SoC (default target)
./build.sh single_cycle dvd_bounce    # Build for Phase 1 Single-Cycle Verilator Sim
```
The script compiles the application, packages it into `out/<target>/<app>/program.hex`, and copies the payload to your clipboard ready to paste into Wozmon (`10000: <paste> \n 10000r` for `multi_cycle`, or `40000:` / `40000r` for `single_cycle`; pass `--no-clip` for headless builds).

### 3. Running the Phase 2 Verilator Simulator (`arty_a7_top`)
Supports both **Linux** (`verilator`, `libsdl2-dev`, `make`) and **macOS** (`brew install verilator sdl2`, plus a RISC-V GCC toolchain to assemble `boot.mem`). You can develop, boot Wozmon, upload programs over UART, and view VGA output identically to the Arty A7-100T without physical FPGA hardware:

```bash
cd cpu/multi-cycle/sim
make -j$(nproc)      # Assembles visual_wozmon320x200.s -> boot.mem & builds Varty_a7_top (macOS: -j$(sysctl -n hw.ncpu))
make run             # Fast VGA mode (VRAM + 60 Hz VBlank cadence)
make run-pin         # Pin-accurate VGA mode (83.46 MHz vga_hs/vga_vs/vga_r/g/b sampling)
make strict          # Rebuild with --x-assign/initial unique to catch uninitialized FF/RAM bugs
make lint            # Strict verilator --lint-only (zero -Wno-* suppressions)
```

For maximum simulation speed, Profile-Guided Optimization (`make pgo-gen`, run briefly with `make run`, then `make pgo-use`) works on both Linux GCC and macOS Apple Clang.

Key simulator features:
- **Exact FPGA Top (`arty_a7_top`)**: Simulates `arty_a7_top.sv` directly (with a behavioral `clk_wiz_0.sv` stub), exercising `BTN0` reset synchronizers, BRAM boot initialization (`boot.mem`), 115200 8N1 UART pins, and VGA pins.
- **Virtual Serial Port (PTY)**: Works on Linux and macOS. On startup, the simulator prints a PTY path (e.g. `/dev/pts/4` or `/dev/ttys004`, or pass `--uart-link /tmp/arty_uart`). Connect with `picocom -b 115200 <pty>` or upload apps identically to hardware using `python3 Programs/tools/serialpaste.py --port <pty> Programs/out/multi_cycle/<app>/program.hex` (automatically runs `<addr>r` with no stray newline so apps stay running; pass `--no-run` to `serialpaste.py` or `bin2hex.py` to load without running).
- **SDL2 Controls & Direct Preloading**: Type or paste (`Ctrl+V` / `PASTE` button) directly in the SDL2 window, toggle `BTN0 RESET` (`F1` / `Ctrl+R`), switch `VGA: FAST` / `VGA: PIN` live (`F2`), or skip UART transfer during rapid C development with `--load ../../../Programs/out/multi_cycle/<app>/program.bin` (and `--headless` for CI/scripted runs).

### 4. Synthesizing Phase 2 for Digilent Arty A7-100T
1. Open Xilinx Vivado (2020.2 or newer recommended).
2. Create an RTL project targeting `xc7a100tcsg324-1`.
3. Add all SystemVerilog files from `cpu/multi-cycle/core/` (including `mul_unit.sv` and `div_unit.sv`).
4. Configure a **Clocking Wizard** IP instance named `clk_wiz_0`:
   - Input: 100 MHz oscillator (`CLK100MHZ`, pin E3).
   - Output 1 (`clk_cpu`): 25.0 MHz (or higher — update `CPU_CLK_FREQ` parameter on `arty_a7_top` to match).
   - Output 2 (`clk_vga`): 83.46 MHz (pixel clock for 1280x800 @ 60 Hz).
5. Add Arty A7 constraint file (`.xdc`) mapping PMOD VGA headers (JB and JC), USB-UART (A9, D10), and Reset Button (D9).
6. Run Synthesis, Implementation, and Generate Bitstream.

---

## 📊 Current State & Roadmap

- [x] **Phase 1: Single-Cycle RV32IM Architecture**
  - [x] Graphical schematic design in *Digital*.
  - [x] Verilog export & Verilator SDL2 simulation harness.
  - [x] Full RV32I instruction set verification.
  - [x] Hardware M-extension (multiplier & sequential divider).
  - [x] Wozmon interactive bootloader.
  - [x] Bare-metal C toolchain with Newlib-nano syscalls.
  - [x] Bare-metal application & test suite (`test_suite`, `wireframe`, `fluid_sim`, `mandelbrot`, `GoL`, `bounce_sim`, `dvd_bounce`, `profiler_workload`).
- [ ] **Phase 2: Multi-Cycle FPGA SoC Architecture**
  - [x] Modular SystemVerilog rewrite.
  - [x] Multi-cycle FSM control logic (`control_fsm.sv`) & STA false-path decoupling (`ir` vs `mem_rdata`).
  - [x] Complete RV32IM datapath (`datapath.sv`) with dedicated 4-stage `DSP48E1` `mul_unit.sv` and 32-step `div_unit.sv`.
  - [x] SoC integration (`soc_top.sv`) with strict MMIO decode & parameterized `CPU_CLK_FREQ` / `RESET_PC`.
  - [x] Dual-port VRAM with tear-free 1280x800 VGA rasterizer (`vga_controller.sv`), software-selectable VSync (`no_vsync`), and synchronized `vblank` / `active_page` status.
  - [x] Hardware UART (`uart.sv`) with 64-byte RX/TX FIFOs, framing/break recovery, and W1C error flags.
  - [x] Top-level Arty A7-100T wrapper (`arty_a7_top.sv`) with per-domain reset synchronizers and synchronous resets across all RTL.
  - [x] Cross-platform (Linux & macOS) Verilator + SDL2 + PTY simulator (`cpu/multi-cycle/sim/`) targeting `arty_a7_top.sv` with Fast & Pin-Accurate VGA modes and PGO support.
  - [x] Target BSP/HAL refactoring (`Programs/bsp/`) unifying `single_cycle` and `multi_cycle` across all C apps.
  - [ ] Vivado bitstream synthesis & timing closure (including post-synthesis evaluation of deferred `ALUOut`/`mem_addr` bypass in `TODO.md`).
  - [ ] Physical hardware bring-up and verification on Arty A7-100T silicon.
  - [ ] `Zicsr` extension & trap/exception support (`TODO.md` Section 3), followed by future OS/kernel experiments.
  - [ ] Fast binary UART bootloader / interactive C BIOS shell & QSPI flash / SD card persistent storage.
- [ ] **Phase 3: RV32IM 5-Stage Pipelined Core**
  - [ ] Pipeline stage registers (`IF/ID`, `ID/EX`, `EX/MEM`, `MEM/WB` register slices).
  - [ ] Hazard detection unit (load-use hazard detection, PC and `IF/ID` stall generation).
  - [ ] Bypass / forwarding unit (`EX/MEM` to EX and `MEM/WB` to EX forwarding).
  - [ ] Control hazard resolution (EX-stage branch target computation and `IF/ID` / `ID/EX` pipeline flush on mispredicts).
- [ ] **Phase 4: RV64 Core, Virtual Memory & Linux Boot**
  - [ ] 64-bit datapath scaling (`XLEN=64` PC, 32 × 64-bit register file, 64-bit ALU + `ADDW`/`SUBW`/`SLLW`, double-word `LD`/`SD`).
  - [ ] Privileged architecture (M-Mode/S-Mode CSRs `mtvec`/`mepc`/`mcause`/`mstatus`, `CSRRW`/`CSRRS`/`CSRRC`, and trap delegation `mideleg`/`medeleg`).
  - [ ] Virtual memory (Sv39 MMU: `SATP` & 3-level page tables, hardware Page Table Walker FSM, TLB cache).
  - [ ] Linux kernel boot (Device Tree FDT setup, OpenSBI bootloader bring-up, and serial console Linux boot confirmation).
