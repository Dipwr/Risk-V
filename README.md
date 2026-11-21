# Risk-V: RV32IM Processor & SoC Architecture

A custom **RISC-V (RV32IM)** processor implementation developed from fundamental digital logic schematics to a synthesizable multi-cycle SystemVerilog SoC targeted for FPGA silicon.

---

## 📌 Project Overview & Goals

The primary goal of **Risk-V** is to build a complete, self-contained RISC-V computing system from scratch:
1. **Instruction Set Architecture**: Full compliance with the unprivileged **RV32I** Base Integer ISA and the **RV32M** Standard Extension for Integer Multiplication and Division.
2. **Two-Stage Evolutionary Roadmap**:
   - **Phase 1 (Single-Cycle & Simulation Platform)**: Educational schematic capture in [Digital](https://github.com/hneemann/Digital), Verilog export, and high-performance cycle-accurate simulation in **Verilator + SDL2** with a rich bare-metal software ecosystem.
   - **Phase 2 (Multi-Cycle Synthesizable Core & FPGA SoC)**: Modular **SystemVerilog** rewrite optimized for physical FPGA hardware (**Digilent Arty A7**), featuring hardware BRAM, dual-port VRAM, hardware VGA pixel generation (1280x800 @ 60 Hz with 4x hardware upscaling), and a custom UART controller.
3. **Full-Stack Bare-Metal Software**:
   - Adapted **Wozmon-style** interactive monitor and hex program loader in RISC-V assembly.
   - Newlib-nano C runtime integration (`boot.s`, `linker.ld`, `syscalls.c`).
   - Rich collection of demo applications: interactive Retro Desktop GUI (MicroUI), Contiki OS, FreeRTOS, 3D wireframe graphics engine, and fluid simulations.

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
- **Target Hardware**: Digilent Arty A7 (Xilinx Artix-7 XC7A35T / XC7A100T).
- **Core RTL**: Written in modular SystemVerilog (`cpu/multi-cycle/core/`).
- **Clock Domains**:
  - `clk_cpu` (25 MHz): Core logic, BRAM, UART, MMIO.
  - `clk_vga` (83.46 MHz): VESA 1280x800 @ 60 Hz CVT pixel clock.
  - Generated via Xilinx Clocking Wizard (`clk_wiz_0`) from onboard 100 MHz oscillator (`CLK100MHZ`).
- **Memory & Video Subsystem**:
  - **Main RAM** (`bram_ram.sv`): 256 KB Block RAM initialized with boot payload.
  - **Dual-Port VRAM** (`vram.sv`): 256 KB true dual-port RAM holding two 128 KB 320x200 RGB565 framebuffers (Port A: CPU R/W, Port B: VGA Rasterizer).
  - **Hardware VGA Controller** (`vga_controller.sv`): Multiplier-free address generator (`(y * 320) + x = (y << 8) + (y << 6) + x`), 4x hardware pixel upscaler (320x200 -> 1280x800), and 16-bit RGB565 to 12-bit RGB444 color reduction for PMOD VGA DAC.
  - **UART Controller** (`uart.sv`): 115200 baud, 8 data bits, 1 stop bit, hardware TX/RX status.

```
+-------------------------------------------------------------------------+
|                              Phase 2 Memory Map                         |
+-------------------------------------------------------------------------+
| Region              | Base Address | End Address  | Size   | Notes      |
+---------------------+--------------+--------------+--------+------------+
| System RAM (BRAM)   | 0x0000_0000  | 0x0003_FFFF  | 256 KB | Boot/Code  |
|   Wozmon Monitor    | 0x0000_0000  | 0x0000_FFFF  | 64 KB  | Bootloader |
|   User Program Area | 0x0001_0000  | 0x0003_FFFF  | 192 KB | Apps/Stack |
| Video RAM (VRAM)    | 0x1000_0000  | 0x1003_FFFF  | 256 KB | Dual-Port  |
|   Framebuffer Page 0| 0x1000_0000  | 0x1001_FFFF  | 128 KB | 320x200    |
|   Framebuffer Page 1| 0x1002_0000  | 0x1003_FFFF  | 128 KB | 320x200    |
| Peripheral MMIO     | 0x2000_0000  | 0x2000_000F  | 16 B   | Hardware   |
|   UART Data (TX/RX) | 0x2000_0000  |              | 4 B    | R/W        |
|   UART Status       | 0x2000_0004  |              | 4 B    | Bit0=RX,B1=TX
|   VGA Display Page  | 0x2000_0008  |              | 4 B    | Page Flip  |
+---------------------+--------------+--------------+--------+------------+
```

---

## ⚙️ Microarchitecture & FSM

The multi-cycle core (`rv32_core.sv`) decouples the control logic into a clean state machine (`control_fsm.sv`) and a synchronous datapath (`datapath.sv`):

```
                       +-------------------+
                       |    STATE_RESET    |
                       +-------------------+
                                 |
                                 v
                       +-------------------+
           +---------->|    STATE_FETCH    |
           |           +-------------------+
           |                     |
           |                     v
           |           +-------------------+
           |           |   STATE_DECODE    |
           |           +-------------------+
           |            /   |     |    \    \
           |   (Branch/JAL/ |     |     \    \
           |    LUI/AUIPC)  |     |      \    \
           |                |     |       \    \
           |                v     v        v    v
           |       +----------+ +------+ +----+ +-----------------+
           |       | STATE_   | |STATE_| |STATE|| STATE_LOAD_REQ  |
           |       | EXECUTE  | | JALR | |STORE| +-----------------+
           |       +----------+ +------+ +----+         |
           |            |           |       |           v
           |            |           |       |   +-----------------+
           |            |           |       |   |  STATE_LOAD_WB  |
           |            |           |       |   +-----------------+
           |            \___________|_______|___________/
           +------------------------+
```

- **Instruction Fetch**: Memory request asserted with `mem_addr = PC`.
- **Instruction Decode & Register Fetch**: Latches Instruction Register (`IR`), reads Register File `rs1` and `rs2` into temporary registers `A` and `B`, executes PC-relative jumps and upper-immediate instructions in-stride.
- **Execute**: Arithmetic and logical operations through the ALU (including M-extension multiplications/divisions).
- **Memory Access**: Single-cycle request for stores, two-cycle request/writeback for loads to handle BRAM access latency.

---

## 💻 Software & Ecosystem

### 1. Wozmon Interactive Bootloader
Ported to RV32I assembly (`Programs/asm/done/visual_wozmon320x200.s`). Runs on power-up and provides an interactive terminal over UART and on-screen framebuffer:
- Inspect memory addresses: `<addr>` (e.g. `10000`).
- Examine memory ranges: `<start>.<end>`.
- Deposit data bytes: `<addr>: <val1> <val2> ...`.
- Execute user programs: `<addr> R` (e.g. `10000 R`).

### 2. Bare-Metal C Runtime & Toolchain
- **Compiler**: Standard RISC-V GCC toolchain (`riscv-none-elf-gcc`, `riscv64-unknown-elf-gcc`, etc.) with flags `-march=rv32im -mabi=ilp32 -O2`.
- **Linker & Runtime**: Custom linker script `Programs/compiler/linker.ld` positioning user programs in RAM with proper stack and heap boundaries.
- **Syscalls**: Lightweight Newlib-nano bridge (`syscalls.c`) supporting `_write` (terminal and on-screen rendering), `_read` (keyboard), and `_sbrk` (dynamic heap allocation via `malloc`).
- **Automation**: `Programs/compiler/build.sh` automatically compiles, links, generates binary/hex payloads, and copies the data to the clipboard for instant pasting into Wozmon via `paste.py` or serial upload via `serialpaste.py`.

### 3. Application Portfolio (`Programs/compiler/programs/`)
- **MicroUI Retro Desktop (`simple_os/`)**: Full graphical desktop environment featuring an interactive GUI calculator, mini paint canvas with mouse support, file explorer with collapsible tree view, terminal, and theme customizer (Windows 95 and Cyberpunk themes).
- **Contiki OS Port (`contiki_os/`)**: Event-driven multitasking OS with CTK graphical toolkit, uBasic interpreter, process manager, and shell tools.
- **FreeRTOS & Nanoshell**: Real-time OS and lightweight console environments.
- **3D Wireframe Graphics Engine (`wireframe/`)**: 3D matrix math rendering rotating wireframe models (Utah teapot, prism, icosahedron) parsed from standard Wavefront OBJ files.
- **Interactive Simulations**:
  - `fluid_sim`: Real-time grid-based fluid dynamics.
  - `GoL`: Conway's Game of Life.
  - `mandlebrot`: Fixed-point Mandelbrot fractal renderer.
  - `dvd_bounce`: Bouncing logo screensaver.

---

## 📁 Repository Layout

```
Risk-V/
├── README.md                      # Project documentation (this file)
├── cpu/
│   ├── riscv-unprivileged.pdf     # RISC-V specification reference
│   ├── riscv-opcodes.pdf          # Instruction encoding reference
│   ├── single-cycle/              # Phase 1: Single-Cycle Core
│   │   ├── cpu_guide.txt          # Bare-metal programmer's reference guide
│   │   ├── digital/               # Digital logic schematics (.dig files)
│   │   └── verilog/               # Verilog export & Verilator SDL2 testbench
│   └── multi-cycle/               # Phase 2: Multi-Cycle FPGA Core
│       └── core/                  # SystemVerilog RTL implementation
│           ├── rv32_pkg.sv        # Package with opcodes, ALU ops, and FSM types
│           ├── rv32_core.sv       # CPU core top (links FSM & Datapath)
│           ├── control_fsm.sv     # Multi-cycle control state machine
│           ├── datapath.sv        # Register file, ALU, immediate gen, PC logic
│           ├── regfile.sv         # 32 x 32-bit dual-read single-write registers
│           ├── alu.sv             # RV32I ALU + RV32M multiplier/divider
│           ├── imm_gen.sv         # Immediate decoder (I, S, B, U, J types)
│           ├── soc_top.sv         # SoC bus arbiter, BRAM, VRAM, and peripherals
│           ├── bram_ram.sv        # 256 KB internal program Block RAM
│           ├── vram.sv            # 256 KB dual-port video RAM
│           ├── vga_controller.sv  # 1280x800 @ 60Hz 4x upscaled VGA controller
│           ├── uart.sv            # Hardware UART module (115200 baud)
│           └── arty_a7_top.sv     # Top-level wrapper for Digilent Arty A7 FPGA
└── Programs/
    ├── asm/                       # Assembly programs and Wozmon bootloaders
    ├── 3d/                        # 3D models (OBJ) and C array converter
    └── compiler/                  # C build system and application suite
        ├── build.sh               # Interactive multi-target build script
        ├── linker.ld              # Bare-metal linker script
        ├── boot.s                 # Startup code (BSS clearing & main jump)
        ├── syscalls.c             # Newlib-nano system calls bridge
        ├── bin2hex.py             # Binary to Wozmon-compatible hex converter
        └── programs/              # Bare-metal applications & OS ports
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
cd Programs/compiler
./build.sh simple_os
```
The script will compile the application, package it into `out/program.hex`, and automatically copy the payload to your system clipboard ready to be pasted directly into Wozmon (`10000: <paste> \n 10000 R`).

### 3. Synthesizing Phase 2 for Digilent Arty A7
1. Open Xilinx Vivado (2020.2 or newer recommended).
2. Create an RTL project targeting `xc7a35ticsg324-1L` or `xc7a100tcsg324-1`.
3. Add all SystemVerilog files from `cpu/multi-cycle/core/`.
4. Configure a **Clocking Wizard** IP instance named `clk_wiz_0`:
   - Input: 100 MHz oscillator (`CLK100MHZ`, pin E3).
   - Output 1 (`clk_cpu`): 25.0 MHz.
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
  - [x] Application portfolio (MicroUI Desktop, Contiki OS, FreeRTOS, 3D wireframe, simulations).
- [ ] **Phase 2: Multi-Cycle FPGA SoC Architecture**
  - [x] Modular SystemVerilog rewrite.
  - [x] Multi-cycle FSM control logic (`control_fsm.sv`).
  - [x] Complete RV32IM datapath (`datapath.sv`).
  - [x] SoC integration (`soc_top.sv`).
  - [x] Dual-port VRAM with 1280x800 VGA rasterizer (`vga_controller.sv`).
  - [x] Hardware UART module (`uart.sv`).
  - [x] Top-level FPGA wrapper for Digilent Arty A7 (`arty_a7_top.sv`).
  - [ ] Vivado bitstream synthesis & timing closure.
  - [ ] Physical hardware bring-up and verification on Arty A7 silicon.
  - [ ] SD card or SPI flash integration for persistent storage.

