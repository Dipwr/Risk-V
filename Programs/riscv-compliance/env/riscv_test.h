#ifndef RISCV_COMPLIANCE_RISCV_TEST_H
#define RISCV_COMPLIANCE_RISCV_TEST_H

#include "encoding.h"

#define TESTNUM gp

#define RVTEST_RV32U
#define RVTEST_RV32M
#define RVTEST_RV64U
#define RVTEST_RV64M
#define RVTEST_RV64S
#define EXTRA_DATA

#ifndef TEST_FUNC_NAME
#define TEST_FUNC_NAME rvtest_entry
#endif

#define RVTEST_CODE_BEGIN \
	.section .text; \
	.globl TEST_FUNC_NAME; \
	.align 2; \
TEST_FUNC_NAME: \
	la   t0, rvtest_saved_regs; \
	sw   ra,   0(t0); \
	sw   sp,   4(t0); \
	sw   gp,   8(t0); \
	sw   tp,  12(t0); \
	sw   s0,  16(t0); \
	sw   s1,  20(t0); \
	sw   s2,  24(t0); \
	sw   s3,  28(t0); \
	sw   s4,  32(t0); \
	sw   s5,  36(t0); \
	sw   s6,  40(t0); \
	sw   s7,  44(t0); \
	sw   s8,  48(t0); \
	sw   s9,  52(t0); \
	sw   s10, 56(t0); \
	sw   s11, 60(t0); \
	csrw mstatus, zero; \
	.weak mtvec_handler; \
	la   t0, mtvec_handler; \
	bnez t0, 1f; \
	la   t0, _rvtest_default_trap; \
1: \
	csrw mtvec, t0; \
	li   TESTNUM, 0; \
	j    _rvtest_start; \
	.align 2; \
_rvtest_default_trap: \
	bnez TESTNUM, _rvtest_trap_fail; \
	csrr t0, mcause; \
	li   t1, 0x8000; \
	or   TESTNUM, t0, t1; \
_rvtest_trap_fail: \
	RVTEST_FAIL; \
_rvtest_start:

#define RVTEST_PASS \
	la   t0, rvtest_saved_regs; \
	lw   ra,   0(t0); \
	lw   sp,   4(t0); \
	lw   gp,   8(t0); \
	lw   tp,  12(t0); \
	lw   s0,  16(t0); \
	lw   s1,  20(t0); \
	lw   s2,  24(t0); \
	lw   s3,  28(t0); \
	lw   s4,  32(t0); \
	lw   s5,  36(t0); \
	lw   s6,  40(t0); \
	lw   s7,  44(t0); \
	lw   s8,  48(t0); \
	lw   s9,  52(t0); \
	lw   s10, 56(t0); \
	lw   s11, 60(t0); \
	li   a0, 0; \
	ret;

#define RVTEST_FAIL \
	mv   a0, TESTNUM; \
	bnez a0, 1f; \
	li   a0, 1; \
1: \
	la   t0, rvtest_saved_regs; \
	lw   ra,   0(t0); \
	lw   sp,   4(t0); \
	lw   gp,   8(t0); \
	lw   tp,  12(t0); \
	lw   s0,  16(t0); \
	lw   s1,  20(t0); \
	lw   s2,  24(t0); \
	lw   s3,  28(t0); \
	lw   s4,  32(t0); \
	lw   s5,  36(t0); \
	lw   s6,  40(t0); \
	lw   s7,  44(t0); \
	lw   s8,  48(t0); \
	lw   s9,  52(t0); \
	lw   s10, 56(t0); \
	lw   s11, 60(t0); \
	ret;

#define RVTEST_CODE_END \
	.align 2;

#define RVTEST_DATA_BEGIN \
	.section .data; \
	.balign 16;

#define RVTEST_DATA_END \
	.balign 4;

#endif /* RISCV_COMPLIANCE_RISCV_TEST_H */
