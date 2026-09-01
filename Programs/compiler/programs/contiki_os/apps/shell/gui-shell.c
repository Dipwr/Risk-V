/*
 * Copyright (c) 2003, Adam Dunkels.
 * All rights reserved.
 * This file is part of the Contiki desktop OS.
 */

#include "contiki.h"
#include "ctk/ctk.h"
#include "shell-basic.h"
#include "shell.h"
#include <stdio.h>
#include <string.h>

#define SHELL_GUI_XSIZE 34
#define SHELL_GUI_YSIZE 12

static struct ctk_window window;

static char log_lines[SHELL_GUI_YSIZE][SHELL_GUI_XSIZE + 1];
static struct ctk_label log_labels[SHELL_GUI_YSIZE];

static struct ctk_separator sep = {
    CTK_SEPARATOR(0, SHELL_GUI_YSIZE, SHELL_GUI_XSIZE)};
static struct ctk_label prompt_label = {
    CTK_LABEL(0, SHELL_GUI_YSIZE + 1, 1, 1, ">")};
static char command[SHELL_GUI_XSIZE - 1] = "";
static struct ctk_textentry command_entry = {
    CTK_TEXTENTRY(2, SHELL_GUI_YSIZE + 1, 20, 1, command, SHELL_GUI_XSIZE - 3)};

static struct ctk_button run_button = {
    CTK_BUTTON(23, SHELL_GUI_YSIZE + 1, 3, "Run")};
static struct ctk_button close_button = {
    CTK_BUTTON(27, SHELL_GUI_YSIZE + 1, 5, "Close")};

PROCESS(gui_shell_process, "Command Shell");

void shell_default_output(const char *text1, int len1, const char *text2,
                          int len2) {
  char line[SHELL_GUI_XSIZE + 1];
  line[0] = '\0';

  if (text1 && len1 > 0) {
    int l = len1 < SHELL_GUI_XSIZE ? len1 : SHELL_GUI_XSIZE;
    strncat(line, text1, l);
  }
  if (text2 && len2 > 0) {
    int rem = SHELL_GUI_XSIZE - strlen(line);
    if (rem > 0) {
      int l = len2 < rem ? len2 : rem;
      strncat(line, text2, l);
    }
  }

  // Scroll log up by 1 line
  for (int i = 0; i < SHELL_GUI_YSIZE - 1; i++) {
    strncpy(log_lines[i], log_lines[i + 1], SHELL_GUI_XSIZE);
    log_lines[i][SHELL_GUI_XSIZE] = '\0';
  }
  strncpy(log_lines[SHELL_GUI_YSIZE - 1], line, SHELL_GUI_XSIZE);
  log_lines[SHELL_GUI_YSIZE - 1][SHELL_GUI_XSIZE] = '\0';

  for (int i = 0; i < SHELL_GUI_YSIZE; i++) {
    CTK_WIDGET_REDRAW(&log_labels[i]);
  }
}

void shell_prompt(char *prompt) {
  if (prompt) {
    shell_default_output(prompt, strlen(prompt), "", 0);
  }
}

PROCESS_THREAD(gui_shell_process, ev, data) {
  PROCESS_BEGIN();

  // Initialize core shell and official offline command modules
  shell_init();
  shell_base64_init();
  shell_crc_init();
  shell_file_init();
  shell_ps_init();
  shell_text_init();
  shell_basic_init();

  // Build CTK Window
  ctk_window_new(&window, SHELL_GUI_XSIZE, SHELL_GUI_YSIZE + 2,
                 "Command Shell");

  for (int i = 0; i < SHELL_GUI_YSIZE; i++) {
    log_lines[i][0] = '\0';
    CTK_LABEL_NEW(&log_labels[i], 0, i, SHELL_GUI_XSIZE, 1, log_lines[i]);
    CTK_WIDGET_ADD(&window, &log_labels[i]);
  }

  CTK_WIDGET_ADD(&window, &sep);
  CTK_WIDGET_ADD(&window, &prompt_label);
  CTK_WIDGET_ADD(&window, &command_entry);
  CTK_WIDGET_ADD(&window, &run_button);
  CTK_WIDGET_ADD(&window, &close_button);

  CTK_WIDGET_FOCUS(&window, &command_entry);
  ctk_window_open(&window);

  shell_start();
  shell_default_output("Contiki RV32IM Shell Ready.", 27, "", 0);
  shell_default_output("Type 'help' for command list.", 29, "", 0);

  while (1) {
    PROCESS_WAIT_EVENT();

    if (ev == ctk_signal_button_activate) {
      if (data == (process_data_t)&run_button) {
        if (strlen(command) > 0) {
          shell_input(command, strlen(command));
          command[0] = '\0';
          CTK_WIDGET_REDRAW(&command_entry);
        }
      } else if (data == (process_data_t)&close_button) {
        shell_stop();
        ctk_window_close(&window);
        PROCESS_EXIT();
      }
    } else if (ev == ctk_signal_window_close &&
               data == (process_data_t)&window) {
      shell_stop();
      ctk_window_close(&window);
      PROCESS_EXIT();
    }
  }

  PROCESS_END();
}