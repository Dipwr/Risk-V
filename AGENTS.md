# Workspace Rules for Risk-V

## 1. Documentation & Backlog Maintenance

Whenever a **significant change** is made to this codebase, update the root [`README.md`](README.md) to stay in sync:
- **Architecture & RTL:** New/modified SystemVerilog modules, clock domains, reset architecture, memory maps, or MMIO registers.
- **Software & Toolchain:** Changes to `build.sh`, `boot.s`, `linker.ld`, `syscalls.c`, bootloaders, `Programs/bsp/`, `Programs/tools/`, or applications under `Programs/apps/`.
- **Roadmap:** Check off completed items and add evolving design goals in **Current State & Roadmap** across all four project phases (Phase 1 Single-Cycle -> Phase 2 Multi-Cycle FPGA SoC -> Phase 3 RV32IM Pipelined -> Phase 4 RV64/Sv39/Linux).

When working from [`cpu/multi-cycle/TODO.md`](cpu/multi-cycle/TODO.md), remove completed items (and empty section headings) once verified; leave explicitly deferred items untouched.

---

## 2. Multi-Cycle RTL & Xilinx Artix-7 (`XC7A100T`) Conventions

All Phase 2 RTL under `cpu/multi-cycle/core/` targets Xilinx Artix-7 synthesis and must follow these rules:
- **Synchronous resets only:** Use `always_ff @(posedge clk)` with synchronous `if (rst)` across all core and peripheral modules. Only the reset synchronizer bridges in `arty_a7_top.sv` should use `or posedge async_rst`.
- **Preserve primitive inference:** Do not add runtime reset loops to RAM arrays (`regfile.sv`, `bram_ram.sv`, `vram.sv`, `uart.sv` FIFOs) or `mul_unit.sv` pipeline registers, or Vivado will fail to infer `RAM32M`/`RAM64M`/`RAMB36E1`/`DSP48E1`. Use `initial` zeroing only where needed for simulation (`regfile.sv`).
- **CDC discipline:** Register signals in the source clock domain before crossing domains, and annotate all multi-FF synchronizer registers with `(* ASYNC_REG = "TRUE" *)`.
- **STA hygiene:** Keep `control_fsm` `always_comb`, `imm_gen`, `rd`, and execution units driven from registered `ir` rather than live `mem_rdata` to prevent structural false critical paths through BRAM.
- **Symbolic constants:** Use named constants and enums from `rv32_pkg.sv` (e.g., `OPC_*`, `FUNCT3_*`, `inside {...}`) instead of raw bit-index shortcuts or magic hex literals.
- **Vivado source list:** Whenever a new `.sv` file is added under `cpu/multi-cycle/core/`, remind the user to add it to their Vivado project sources.

---

## 3. Verification Before Completing RTL Changes

- **Strict Verilator lint:** After modifying any SystemVerilog module under `cpu/multi-cycle/core/`, run `make -C cpu/multi-cycle/sim lint` (which runs `verilator --lint-only` with **zero `-Wno-*` suppressions** on `rv32_core`, `soc_top`, and `arty_a7_top` with `cpu/multi-cycle/sim/clk_wiz_0.sv`), verifying 0 errors and 0 warnings.
- **Keep core RTL simulation-clean & sim harness portable:** Keep `cpu/multi-cycle/core/` free of simulation-only stubs or test hooks; expose internal signals for the simulator via `cpu/multi-cycle/sim/sim.vlt` instead. Keep `cpu/multi-cycle/sim/` portable across **Linux and macOS** (`<util.h>` vs `<pty.h>`, Clang `-flto=thin` vs GCC `-flto=auto`, no `-lutil` or Linux-only flags on `Darwin`).
- **Functional simulation:** Verify behavioral changes with `verilator --binary --assert` testbenches in the conversation scratch directory — do not commit temporary testbenches or `obj_*` build artifacts into `cpu/multi-cycle/core/`.
