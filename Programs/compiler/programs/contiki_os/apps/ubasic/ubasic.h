#ifndef UBASIC_H_
#define UBASIC_H_

#include "contiki.h"

void ubasic_init(const char *program);
void ubasic_run(void);
int ubasic_finished(void);
void ubasic_set_variable(char var, int value);
int ubasic_get_variable(char var);

typedef void (*ubasic_output_fn)(const char *str);
void ubasic_set_output(ubasic_output_fn fn);

#endif /* UBASIC_H_ */