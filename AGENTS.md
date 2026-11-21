# Workspace Rules for Risk-V

## Documentation Maintenance Rule

Whenever a **significant change** is made to this codebase, the root [`README.md`](file:///home/dpa/Documents/code/Digital_Logic/Digital/Risk-V/README.md) MUST be updated to reflect it:

1. **Architecture & RTL Changes**:
   - New or modified SystemVerilog / Verilog modules (e.g. CPU core, datapath, FSM controller, peripherals, SoC interconnect).
   - Modifications to clock domains, PLL/clock wizards, or FPGA top-level pinouts.
   - Adjustments to memory maps, MMIO address ranges, or peripheral registers (UART, VGA, VRAM, RAM, timers, etc.).

2. **Software & Toolchain Changes**:
   - New bare-metal applications, libraries, or operating system ports added to `Programs/compiler/programs/`.
   - Changes to the build pipeline (`build.sh`), compiler flags, startup code (`boot.s`), linker script (`linker.ld`), or Newlib-nano syscalls (`syscalls.c`).
   - Updates to bootloaders (Wozmon) or memory upload utilities (`bin2hex.py`, `paste.py`, `serialpaste.py`).

3. **Milestones & Roadmap Progress**:
   - Check off completed items in the **Current State & Roadmap** section of `README.md`.
   - Add new roadmap items or design goals as the project evolves (e.g. Vivado synthesis, bitstream generation, on-board Arty A7 testing, SD card / SPI flash integration).

