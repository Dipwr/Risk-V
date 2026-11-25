#ifndef _DHRY_UTIL_H
#define _DHRY_UTIL_H

#include <stdint.h>

#define read_csr(reg)                                                          \
	({                                                                         \
		uint32_t __tmp;                                                        \
		__asm__ volatile("csrr %0, " #reg : "=r"(__tmp));                      \
		__tmp;                                                                 \
	})

extern void setStats(int enable);

#endif /* _DHRY_UTIL_H */
