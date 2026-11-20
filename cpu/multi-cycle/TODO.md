# Multi-Cycle RV32IM Core & SoC — Known Issues & TODO List

Target: **Digilent Arty A7-100T (`XC7A100T`)**  
Directory: `cpu/multi-cycle/core/`

---

## 1. Architectural & Timing Bottlenecks

- [ ] **1.3 [Deferred] Re-evaluate `ALUOut` / `MDR` Memory Staging Registers (`datapath.sv`, `control_fsm.sv`)**
  - **Files:** `datapath.sv:62`, `datapath.sv:68`, `datapath.sv:121-172`, `datapath.sv:218-223`, `control_fsm.sv:203-225`, `soc_top.sv:34-55`
  - **Notes:** Deferred until post-**1.2** Vivado `report_timing_summary` results are checked:
    - **`MDR` (skip unless pipelining `FETCH` too):** `STATE_DECODE` already shares the same BRAM read mux + cross-die routing path without a staging register, so adding `MDR` (+1 cycle per `LOAD`) only trims ~1–2 ns of local byte/sign-extend muxing while `STATE_DECODE` remains at nearly the same Fmax ceiling.
    - **`ALUOut` (conditional on timing):** Adds +1 cycle to both `STORE` (3->4) and `LOAD` (4->5), costing ~9% average CPI; only worth adding if Vivado timing shows `STATE_LOAD_REQ`/`STATE_STORE` (`u_alu -> mem_addr/mem_wbe -> 128 BRAMs`) trailing `STATE_DECODE` by >10–15%.
    - **`mem_addr` ALU mux bypass (0-cycle option):** Even after removing **1.1**, `mem_addr` in `STATE_LOAD_REQ`/`STATE_STORE` still traverses `u_alu`'s 10:1 output mux (`datapath.sv:68, 218-223`); if timing shows `STATE_LOAD_REQ`/`STATE_STORE` as the bottleneck, tapping a dedicated `reg_a + imm` adder directly for `MEM_ADDR_ALU` avoids `alu_src_a`, `alu_src_b`, and the 10-op ALU mux with **0 extra cycles**.

---

## 3. Pre-`Zicsr` Preparation

- [ ] **3.1 Fix `OPC_SYSTEM` Immediate/CSR Address Decoding (`imm_gen.sv`)**
  - **Files:** `imm_gen.sv:14-16`
  - **Issue:** `OPC_SYSTEM` is grouped with I-type instructions and sign-extends `instr[31:20]`. For `Zicsr`, `instr[31:20]` is an unsigned 12-bit CSR address (`csr_addr`), while `CSRRWI`/`CSRRSI`/`CSRRCI` use the 5-bit zero-extended immediate `{27'b0, instr[19:15]}` (`zimm`).

- [ ] **3.2 Tighten Illegal-Instruction & Misaligned-Target Decode (`control_fsm.sv`, `datapath.sv`)**
  - **Files:** `control_fsm.sv:51-70`, `control_fsm.sv:175-197`, `datapath.sv:102-103`
  - **Issue:** Decode currently accepts arbitrary `funct7` values on `OPC_OP` and `OPC_OP_IMM` shifts, arbitrary `funct3` values on `OPC_BRANCH`/`OPC_LOAD`/`OPC_STORE`, and ignores `target[1] == 1` on `JAL`/`JALR`/taken `BRANCH` (Instruction Address Misaligned without `C` extension). Tighten decode validation in `STATE_DECODE` if implementing `mcause`/exception traps with `Zicsr`.

- [ ] **3.3 Implement `Zicsr` Zero-Register Side-Effect Suppression Rules**
  - **Goal:** Ensure `CSRRW`/`CSRRWI` with `rd == x0` suppresses CSR read side effects, and `CSRRS`/`CSRRC`/`CSRRSI`/`CSRRCI` with `rs1 == x0` / `zimm == 0` suppresses CSR writes (essential so reading read-only CSRs like `mcycle`/`minstret` via `csrrs rd, csr, x0` does not raise an illegal-instruction trap).
