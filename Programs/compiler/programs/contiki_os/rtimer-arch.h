#ifndef RTIMER_ARCH_H_
#define RTIMER_ARCH_H_

#include "contiki-conf.h"

#define RTIMER_ARCH_SECOND CLOCK_CONF_SECOND

// Forward declaration of clock_time from main.c
clock_time_t clock_time(void);

#define rtimer_arch_now() ((rtimer_clock_t)clock_time())

static inline void rtimer_arch_init(void) {}
static inline void rtimer_arch_schedule(rtimer_clock_t t) { (void)t; }

#endif /* RTIMER_ARCH_H_ */