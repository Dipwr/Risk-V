/*
 * Text Editor Application for Contiki OS & CTK Desktop
 */

#include "editor.h"
#include "cfs/cfs.h"
#include "ctk/ctk-draw.h"
#include "ctk/ctk.h"
#include <stdio.h>
#include <string.h>

#define EDITOR_WIDTH 36
#define EDITOR_HEIGHT 18
#define EDITOR_MAX_LINES 11
#define EDITOR_LINE_LEN 34
#define EDITOR_MAX_PATH 24

static struct ctk_window window;

static char filename_buf[EDITOR_MAX_PATH] = "readme.txt";
static struct ctk_label file_label = {CTK_LABEL(0, 0, 5, 1, "File:")};
static struct ctk_textentry file_entry = {
    CTK_TEXTENTRY(6, 0, 14, 1, filename_buf, EDITOR_MAX_PATH - 1)};

static struct ctk_button open_button = {CTK_BUTTON(22, 0, 4, "Open")};
static struct ctk_button save_button = {CTK_BUTTON(28, 0, 4, "Save")};

static struct ctk_separator sep1 = {CTK_SEPARATOR(0, 1, EDITOR_WIDTH)};

static char line_buffers[EDITOR_MAX_LINES][EDITOR_LINE_LEN + 1];
static struct ctk_textentry edit_entries[EDITOR_MAX_LINES];

static struct ctk_separator sep2 = {
    CTK_SEPARATOR(0, EDITOR_HEIGHT - 3, EDITOR_WIDTH)};

static struct ctk_button clear_button = {
    CTK_BUTTON(0, EDITOR_HEIGHT - 2, 5, "Clear")};
static struct ctk_button close_button = {
    CTK_BUTTON(28, EDITOR_HEIGHT - 2, 5, "Close")};

static char status_buf[EDITOR_WIDTH] = "Ready";
static struct ctk_label status_label = {
    CTK_LABEL(7, EDITOR_HEIGHT - 2, 20, 1, status_buf)};

PROCESS(editor_process, "Text Editor");

static void set_status(const char *msg) {
  strncpy(status_buf, msg, sizeof(status_buf) - 1);
  status_buf[sizeof(status_buf) - 1] = '\0';
  CTK_WIDGET_REDRAW(&status_label);
}

static void clear_buffer(void) {
  for (int i = 0; i < EDITOR_MAX_LINES; i++) {
    line_buffers[i][0] = '\0';
    CTK_WIDGET_REDRAW(&edit_entries[i]);
  }
}

static void load_file(const char *fname) {
  int fd = cfs_open(fname, CFS_READ);
  if (fd < 0) {
    set_status("Cannot open file!");
    return;
  }

  clear_buffer();

  char ch;
  int cur_line = 0;
  int cur_col = 0;
  int total_bytes = 0;

  while (cfs_read(fd, &ch, 1) == 1) {
    total_bytes++;
    if (ch == '\r') {
      continue;
    }
    if (ch == '\n') {
      if (cur_line < EDITOR_MAX_LINES) {
        line_buffers[cur_line][cur_col] = '\0';
        cur_line++;
        cur_col = 0;
      }
      continue;
    }
    if (cur_line < EDITOR_MAX_LINES && cur_col < EDITOR_LINE_LEN) {
      line_buffers[cur_line][cur_col++] = ch;
      line_buffers[cur_line][cur_col] = '\0';
    }
  }

  cfs_close(fd);

  for (int i = 0; i < EDITOR_MAX_LINES; i++) {
    CTK_WIDGET_REDRAW(&edit_entries[i]);
  }

  char msg[32];
  snprintf(msg, sizeof(msg), "Loaded %d bytes", total_bytes);
  set_status(msg);
}

static void save_file(const char *fname) {
  if (!fname || strlen(fname) == 0) {
    set_status("Invalid filename!");
    return;
  }

  int fd = cfs_open(fname, CFS_WRITE);
  if (fd < 0) {
    set_status("Cannot save file!");
    return;
  }

  int total_written = 0;
  for (int i = 0; i < EDITOR_MAX_LINES; i++) {
    int len = strlen(line_buffers[i]);
    if (len > 0) {
      cfs_write(fd, line_buffers[i], len);
      cfs_write(fd, "\n", 1);
      total_written += len + 1;
    }
  }

  cfs_close(fd);

  char msg[32];
  snprintf(msg, sizeof(msg), "Saved %d bytes", total_written);
  set_status(msg);
}

void editor_open_file(const char *filename) {
  if (filename && strlen(filename) > 0) {
    strncpy(filename_buf, filename, sizeof(filename_buf) - 1);
    filename_buf[sizeof(filename_buf) - 1] = '\0';
  }
  process_start(&editor_process, NULL);
}

PROCESS_THREAD(editor_process, ev, data) {
  PROCESS_BEGIN();

  ctk_window_new(&window, EDITOR_WIDTH, EDITOR_HEIGHT, "Text Editor");

  CTK_WIDGET_ADD(&window, &file_label);
  CTK_WIDGET_ADD(&window, &file_entry);
  CTK_WIDGET_ADD(&window, &open_button);
  CTK_WIDGET_ADD(&window, &save_button);
  CTK_WIDGET_ADD(&window, &sep1);

  for (int i = 0; i < EDITOR_MAX_LINES; i++) {
    line_buffers[i][0] = '\0';
    CTK_TEXTENTRY_NEW(&edit_entries[i], 0, 2 + i, EDITOR_LINE_LEN, 1,
                      line_buffers[i], EDITOR_LINE_LEN);
    CTK_WIDGET_ADD(&window, &edit_entries[i]);
  }

  CTK_WIDGET_ADD(&window, &sep2);
  CTK_WIDGET_ADD(&window, &clear_button);
  CTK_WIDGET_ADD(&window, &status_label);
  CTK_WIDGET_ADD(&window, &close_button);

  CTK_WIDGET_FOCUS(&window, &edit_entries[0]);
  ctk_window_open(&window);

  if (strlen(filename_buf) > 0) {
    load_file(filename_buf);
    CTK_WIDGET_REDRAW(&file_entry);
  }

  while (1) {
    PROCESS_WAIT_EVENT();

    if (ev == ctk_signal_button_activate) {
      if (data == (process_data_t)&open_button) {
        load_file(filename_buf);
      } else if (data == (process_data_t)&save_button) {
        save_file(filename_buf);
      } else if (data == (process_data_t)&clear_button) {
        clear_buffer();
        set_status("Buffer cleared");
      } else if (data == (process_data_t)&close_button) {
        ctk_window_close(&window);
        PROCESS_EXIT();
      }
    } else if (ev == ctk_signal_window_close &&
               data == (process_data_t)&window) {
      ctk_window_close(&window);
      PROCESS_EXIT();
    }
  }

  PROCESS_END();
}