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
