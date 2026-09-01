#ifndef __LOADER_ARCH_H__
#define __LOADER_ARCH_H__

#include "contiki.h"
#include "sys/dsc.h"

struct dsc *loader_arch_load_dsc(char *name);
unsigned char loader_arch_load(char *name, char *arg);
void loader_arch_unload(void);
void loader_arch_unload_dsc(struct dsc *dsc);

#endif /* __LOADER_ARCH_H__ */