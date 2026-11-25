#include "bsp.h"
#include "coremark.h"
#include "core_portme.h"

#if VALIDATION_RUN
volatile ee_s32 seed1_volatile = 0x3415;
volatile ee_s32 seed2_volatile = 0x3415;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PERFORMANCE_RUN
volatile ee_s32 seed1_volatile = 0x0;
volatile ee_s32 seed2_volatile = 0x0;
volatile ee_s32 seed3_volatile = 0x66;
#endif
#if PROFILE_RUN
volatile ee_s32 seed1_volatile = 0x8;
volatile ee_s32 seed2_volatile = 0x8;
volatile ee_s32 seed3_volatile = 0x8;
#endif
volatile ee_s32 seed4_volatile = ITERATIONS;
volatile ee_s32 seed5_volatile = 0;

static inline uint64_t read_cycle64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("rdcycleh %0" : "=r"(hi0));
		__asm__ volatile("rdcycle  %0" : "=r"(lo));
		__asm__ volatile("rdcycleh %0" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

static inline uint64_t read_instret64(void) {
	uint32_t hi0, lo, hi1;
	do {
		__asm__ volatile("rdinstreth %0" : "=r"(hi0));
		__asm__ volatile("rdinstret  %0" : "=r"(lo));
		__asm__ volatile("rdinstreth %0" : "=r"(hi1));
	} while (hi0 != hi1);
	return ((uint64_t)hi0 << 32) | lo;
}

CORETIMETYPE barebones_clock(void) {
	return (CORETIMETYPE)read_cycle64();
}

#define GETMYTIME(_t)              (*_t = barebones_clock())
#define MYTIMEDIFF(fin, ini)       ((fin) - (ini))
#define TIMER_RES_DIVIDER          1
#define SAMPLE_TIME_IMPLEMENTATION 1
#define EE_TICKS_PER_SEC           (CPU_CLK_FREQ / TIMER_RES_DIVIDER)

static CORETIMETYPE start_time_val, stop_time_val;
static uint64_t start_instret_val, stop_instret_val;

void start_time(void) {
	start_instret_val = read_instret64();
	GETMYTIME(&start_time_val);
}

void stop_time(void) {
	GETMYTIME(&stop_time_val);
	stop_instret_val = read_instret64();
}

CORE_TICKS get_time(void) {
	return (CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
}

secs_ret time_in_secs(CORE_TICKS ticks) {
	return ((secs_ret)ticks) / (secs_ret)EE_TICKS_PER_SEC;
}

ee_u32 default_num_contexts = 1;

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

void portable_init(core_portable *p, int *argc, char *argv[]) {
	(void)argc;
	(void)argv;
	bsp_set_vsync(0);
	bsp_set_page(0);
	printf("\n====================================================\n");
	printf(" EEMBC CoreMark (RV32IM_Zicsr_Zicntr @ %lu MHz)\n",
	       (unsigned long)(CPU_CLK_FREQ / 1000000ULL));
	printf(" Iterations: %d\n", (int)ITERATIONS);
	printf("====================================================\n");
	p->portable_id = 1;
}

void portable_fini(core_portable *p) {
	uint64_t cycles = stop_time_val - start_time_val;
	uint64_t instret = stop_instret_val - start_instret_val;
	double cpi = instret ? ((double)cycles / (double)instret) : 0.0;
	double secs = (double)cycles / (double)EE_TICKS_PER_SEC;
	double cm_score = (secs > 0.0) ? ((double)ITERATIONS / secs) : 0.0;
	double cm_per_mhz = cm_score / ((double)CPU_CLK_FREQ / 1e6);
	char cyc_buf[24], inst_buf[24];
	fmt_u64(cyc_buf, cycles);
	fmt_u64(inst_buf, instret);

	printf("----------------------------------------------------\n");
	printf(" Cycles       : %s\n", cyc_buf);
	printf(" Instructions : %s\n", inst_buf);
	printf(" Avg CPI      : %.3f\n", cpi);
	printf(" CoreMark/MHz : %.4f\n", cm_per_mhz);
	printf(" CoreMark@%luM: %.2f\n",
	       (unsigned long)(CPU_CLK_FREQ / 1000000ULL), cm_score);
	printf("====================================================\n");

	p->portable_id = 0;
}
