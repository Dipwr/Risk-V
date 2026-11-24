# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

No open items — Phase 2 timing closed at **84 MHz** (`clk_cpu`) / **83.46 MHz** (`clk_vga`) after implementing the 0-cycle `eff_addr` bypass and evaluating and skipping `ALUOut`/`MDR` staging registers.
