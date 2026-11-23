#ifndef RISCV_COMPLIANCE_ENCODING_H
#define RISCV_COMPLIANCE_ENCODING_H

/* Privilege modes */
#define PRV_U 0
#define PRV_S 1
#define PRV_M 3

/* mstatus fields */
#define MSTATUS_MIE  0x00000008
#define MSTATUS_MPIE 0x00000080
#define MSTATUS_MPP  0x00001800
#define MSTATUS_FS   0x00006000
#define MSTATUS_MPRV 0x00020000
#define MSTATUS_SUM  0x00040000
#define MSTATUS_TVM  0x00100000
#define MSTATUS_TSR  0x00400000

/* sstatus fields (referenced by rv64si/csr.S / illegal.S under #ifdefs) */
#define SSTATUS_SIE  0x00000002
#define SSTATUS_SPIE 0x00000020
#define SSTATUS_SPP  0x00000100
#define SSTATUS_SUM  0x00040000
#define SSTATUS_MXR  0x00080000
#define SSTATUS_UXL  0x0000000300000000ULL

/* mip fields */
#define MIP_SSIP     (1 << 1)

/* Exception cause codes */
#define CAUSE_MISALIGNED_FETCH    0x0
#define CAUSE_FETCH_ACCESS        0x1
#define CAUSE_ILLEGAL_INSTRUCTION 0x2
#define CAUSE_BREAKPOINT          0x3
#define CAUSE_MISALIGNED_LOAD     0x4
#define CAUSE_LOAD_ACCESS         0x5
#define CAUSE_MISALIGNED_STORE    0x6
#define CAUSE_STORE_ACCESS        0x7
#define CAUSE_USER_ECALL          0x8
#define CAUSE_SUPERVISOR_ECALL    0x9
#define CAUSE_MACHINE_ECALL       0xb
#define CAUSE_FETCH_PAGE_FAULT    0xc
#define CAUSE_LOAD_PAGE_FAULT     0xd
#define CAUSE_STORE_PAGE_FAULT    0xf

#endif /* RISCV_COMPLIANCE_ENCODING_H */
