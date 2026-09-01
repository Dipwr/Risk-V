#include "cfs/cfs.h"
#include "contiki.h"
#include "shell.h"
#include "ubasic.h"
#include <stdio.h>
#include <string.h>

#define MAX_PROG_SIZE 2048

static char prog_buffer[MAX_PROG_SIZE];

/*---------------------------------------------------------------------------*/
PROCESS(shell_basic_process, "basic");
SHELL_COMMAND(basic_command, "basic", "basic <file.bas>: run a BASIC program",
              &shell_basic_process);

PROCESS(shell_exec_process, "exec");
SHELL_COMMAND(exec_command, "exec", "exec <file.sh>: execute shell script",
              &shell_exec_process);
/*---------------------------------------------------------------------------*/
static void basic_print_output(const char *text) {
  shell_output_str(&basic_command, (char *)text, "");
}

PROCESS_THREAD(shell_basic_process, ev, data) {
  PROCESS_BEGIN();

  if (data == NULL || strlen((char *)data) == 0) {
    shell_output_str(&basic_command, "Usage: basic <filename.bas>", "");
    PROCESS_EXIT();
  }

  int fd = cfs_open(data, CFS_READ);
  if (fd < 0) {
    shell_output_str(&basic_command, "basic: could not open file: ", data);
    PROCESS_EXIT();
  }

  int len = cfs_read(fd, prog_buffer, sizeof(prog_buffer) - 1);
  cfs_close(fd);

  if (len <= 0) {
    shell_output_str(&basic_command, "basic: empty file", "");
    PROCESS_EXIT();
  }
  prog_buffer[len] = '\0';

  shell_output_str(&basic_command, "--- Running BASIC Program ---", "");
  ubasic_set_output(basic_print_output);
  ubasic_init(prog_buffer);

  while (!ubasic_finished()) {
    ubasic_run();
  }

  shell_output_str(&basic_command, "--- Program Finished ---", "");
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(shell_exec_process, ev, data) {
  static int fd = -1;
  static char line[64];
  static int line_idx = 0;
  char ch;

  PROCESS_BEGIN();

  if (data == NULL) {
    shell_output_str(&exec_command, "Usage: exec <script.sh>", "");
    PROCESS_EXIT();
  }

  fd = cfs_open(data, CFS_READ);
  if (fd < 0) {
    shell_output_str(&exec_command, "exec: cannot open file: ", data);
    PROCESS_EXIT();
  }

  line_idx = 0;
  while (cfs_read(fd, &ch, 1) == 1) {
    if (ch == '\r')
      continue;
    if (ch == '\n') {
      line[line_idx] = '\0';
      if (line_idx > 0 && line[0] != '#') {
        shell_input(line, line_idx);
      }
      line_idx = 0;
      continue;
    }
    if (line_idx < sizeof(line) - 1) {
      line[line_idx++] = ch;
    }
  }
  if (line_idx > 0) {
    line[line_idx] = '\0';
    shell_input(line, line_idx);
  }

  cfs_close(fd);
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/
void shell_basic_init(void) {
  shell_register_command(&basic_command);
  shell_register_command(&exec_command);
}