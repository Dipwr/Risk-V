/*
 * Copyright (c) 2008, Swedish Institute of Computer Science.
 * All rights reserved.
 * This file is part of the Contiki desktop OS.
 */

#include "shell.h"
#include "contiki-lib.h"
#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct shell_command *commands = NULL;
int shell_event_input;

PROCESS(shell_process, "Shell");

void shell_init(void) { shell_event_input = process_alloc_event(); }

void shell_start(void) { process_start(&shell_process, NULL); }

void shell_stop(void) { process_exit(&shell_process); }

void shell_register_command(struct shell_command *c) {
  struct shell_command *i;
  for (i = commands; i != NULL; i = i->next) {
    if (strcmp(i->command, c->command) == 0) {
      return;
    }
  }
  c->next = commands;
  commands = c;
}

void shell_unregister_command(struct shell_command *c) {
  struct shell_command *i, *prev = NULL;
  for (i = commands; i != NULL; i = i->next) {
    if (i == c) {
      if (prev == NULL) {
        commands = i->next;
      } else {
        prev->next = i->next;
      }
      return;
    }
    prev = i;
  }
}

void shell_output(struct shell_command *c, void *data1, int size1,
                  const void *data2, int size2) {
  (void)c;
  shell_default_output((const char *)data1, size1, (const char *)data2, size2);
}

void shell_output_str(struct shell_command *c, char *str1, const char *str2) {
  (void)c;
  shell_default_output(str1, str1 ? strlen(str1) : 0, str2,
                       str2 ? strlen(str2) : 0);
}

unsigned long shell_strtolong(const char *str, const char **retstr) {
  return strtoul(str, (char **)retstr, 10);
}

unsigned long shell_time(void) { return clock_seconds(); }

void shell_set_time(unsigned long seconds) { (void)seconds; }

/* Built-in Help Commands */
SHELL_COMMAND(help_command, "help", "help: list all available commands",
              &shell_process);
SHELL_COMMAND(question_command, "?", "?: list all available commands",
              &shell_process);

void shell_input(char *commandline, int commandline_len) {
  char *command;
  struct shell_command *c;
  int len;

  while (*commandline == ' ') {
    commandline++;
    commandline_len--;
  }

  if (commandline_len == 0 || *commandline == '\0') {
    return;
  }

  command = commandline;
  len = strcspn(command, " \r\n");

  /* Handle built-in help */
  if ((strncmp(command, "help", len) == 0 && len == 4) ||
      (strncmp(command, "?", len) == 0 && len == 1)) {
    shell_output_str(NULL, "Available commands:", "");
    for (c = commands; c != NULL; c = c->next) {
      char buf[64];
      snprintf(buf, sizeof(buf), "  %-8s - %s", c->command,
               c->description ? c->description : "");
      shell_output_str(NULL, buf, "");
    }
    return;
  }

  /* Dispatch registered command plugins */
  for (c = commands; c != NULL; c = c->next) {
    if (strncmp(c->command, command, len) == 0 && c->command[len] == '\0') {
      char *args = command + len;
      while (*args == ' ')
        args++;
      struct shell_input input;
      input.data1 = args;
      input.data2 = "";
      input.len1 = strlen(args);
      input.len2 = 0;
      process_start(c->process, (char *)args);
      process_post_synch(c->process, shell_event_input, &input);
      return;
    }
  }

  shell_output_str(NULL, "Unknown command: ", command);
  shell_output_str(NULL, "Type 'help' for available commands.", "");
}

PROCESS_THREAD(shell_process, ev, data) {
  PROCESS_BEGIN();
  shell_register_command(&help_command);
  shell_register_command(&question_command);
  while (1) {
    PROCESS_WAIT_EVENT();
  }
  PROCESS_END();
}