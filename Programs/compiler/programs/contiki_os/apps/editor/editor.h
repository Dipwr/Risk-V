#ifndef EDITOR_H_
#define EDITOR_H_

#include "contiki.h"

PROCESS_NAME(editor_process);

void editor_open_file(const char *filename);

#endif /* EDITOR_H_ */