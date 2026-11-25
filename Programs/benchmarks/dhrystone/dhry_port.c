#include "bsp.h"
#include <stdint.h>
#include <stdio.h>

#ifndef CPU_CLK_FREQ
#define CPU_CLK_FREQ 84000000ULL
#endif

#ifndef NUMBER_OF_RUNS
#define NUMBER_OF_RUNS 500
#endif

static inline uint64_t read_mcycle64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("csrr %0, mcycleh" : "=r"(hi0));
		__asm__ volatile("csrr %0, mcycle"  : "=r"(lo));
		__asm__ volatile("csrr %0, mcycleh" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

static inline uint64_t read_minstret64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("csrr %0, minstreth" : "=r"(hi0));
		__asm__ volatile("csrr %0, minstret"  : "=r"(lo));
		__asm__ volatile("csrr %0, minstreth" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

static uint64_t g_start_cyc = 0;
static uint64_t g_start_inst = 0;

static void fmt_u64(char *buf, uint64_t val) {
	char tmp[24];
	int i = 0;
	if (val == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	while (val > 0) {
		tmp[i++] = (char)('0' + (val % 10ULL));
		val /= 10ULL;
	}
	int j = 0;
	while (i > 0) {
		buf[j++] = tmp[--i];
	}
	buf[j] = '\0';
}

void setStats(int enable) {
	if (enable) {
		bsp_set_vsync(0);
		bsp_set_page(0);
		g_start_inst = read_minstret64();
		g_start_cyc = read_mcycle64();
	} else {
		uint64_t end_cyc = read_mcycle64();
		uint64_t end_inst = read_minstret64();
		uint64_t cycles = end_cyc - g_start_cyc;
		uint64_t instret = end_inst - g_start_inst;
		double cpi = instret ? ((double)cycles / (double)instret) : 0.0;
		double dhry_per_sec =
			cycles ? (((double)NUMBER_OF_RUNS * (double)CPU_CLK_FREQ) / (double)cycles)
			       : 0.0;
		double dmips = dhry_per_sec / 1757.0;
		double dmips_per_mhz = dmips / ((double)CPU_CLK_FREQ / 1e6);
		char cyc_buf[24], inst_buf[24];
		fmt_u64(cyc_buf, cycles);
		fmt_u64(inst_buf, instret);

		printf("\n====================================================\n");
		printf(" Dhrystone 2.2 Results (RV32IM @ %lu MHz)\n",
		       (unsigned long)(CPU_CLK_FREQ / 1000000ULL));
		printf(" Runs         : %d\n", (int)NUMBER_OF_RUNS);
		printf(" Cycles       : %s\n", cyc_buf);
		printf(" Instructions : %s\n", inst_buf);
		printf(" Avg CPI      : %.3f\n", cpi);
		printf(" DMIPS/MHz    : %.4f\n", dmips_per_mhz);
		printf(" DMIPS @ %luM : %.2f\n",
		       (unsigned long)(CPU_CLK_FREQ / 1000000ULL), dmips);
		printf("====================================================\n");
	}
}
