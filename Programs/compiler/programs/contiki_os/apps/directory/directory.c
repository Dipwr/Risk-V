/*
 * Copyright (c) 2003, Adam Dunkels.
 * All rights reserved.
 *
 * Modified to support browsing all CFS files alongside .dsc programs.
 */

#include <stdlib.h>
#include <string.h>

#include "cfs/cfs.h"
#include "contiki.h"
#include "ctk/ctk-draw.h"
#include "ctk/ctk.h"

#include "program-handler.h"

#define FILENAMELEN 24
#define MAX_NUMFILES 40
#define WIDTH 36
#define HEIGHT 22

static char filenames[MAX_NUMFILES][FILENAMELEN + 1];
static struct dsc *dscs[MAX_NUMFILES];
static unsigned char numfiles, morestart, filenameptr;

#if CTK_CONF_ICON_TEXTMAPS
static char file_textmap[9] = {'|', '=', '|', '|', ' ', '|', '+', '-', '+'};
#endif

#if CTK_CONF_ICONS
static struct ctk_icon default_icons[MAX_NUMFILES];
#endif
static struct dsc default_dscs[MAX_NUMFILES];

static struct ctk_window window;

static struct ctk_label description = {CTK_LABEL(0, HEIGHT - 1, WIDTH, 1, "")};

static char autoexit = 1;
static struct ctk_button autoexitbutton = {
    CTK_BUTTON(WIDTH / 2 - 9, 20, 9, "Auto-exit")};
static char autoexiton[] = "is On ";
static char autoexitoff[] = "is Off";
static struct ctk_label autoexitlabel = {
    CTK_LABEL(WIDTH / 2 - 9 + 12, 20, 6, 1, autoexiton)};

static struct ctk_button morebutton = {CTK_BUTTON(0, 20, 4, "More")};

static struct ctk_button backbutton = {CTK_BUTTON(0, 20, 4, "Back")};

static struct ctk_button reloadbutton = {CTK_BUTTON(30, 20, 6, "Reload")};

PROCESS(directory_process, "Directory browser");

AUTOSTART_PROCESSES(&directory_process);

static unsigned char width, height;

#define LOADING_DIR 1
#define LOADING_DSC 2
static char loading = 0;
static struct cfs_dir dir;

/*-----------------------------------------------------------------------------------*/
static void show_statustext(char *text) {
  ctk_label_set_text(&description, text);
  CTK_WIDGET_REDRAW(&description);
}
/*-----------------------------------------------------------------------------------*/
static void startloading(void) {
  if (cfs_opendir(&dir, "/") != 0) {
    show_statustext("Cannot open directory");
    loading = 0;
  } else {
    loading = LOADING_DIR;
    process_post(&directory_process, PROCESS_EVENT_CONTINUE, NULL);
    numfiles = 0;
  }
}
/*-----------------------------------------------------------------------------------*/
static void makewindow(unsigned char i) {
  unsigned char x, y;

  ctk_window_clear(&window);
  CTK_WIDGET_SET_YPOS(&description, height - 3);
  CTK_WIDGET_SET_WIDTH(&description, width);
  CTK_WIDGET_ADD(&window, &description);

  morestart = i;

  x = 0;
  y = 1;
  for (; dscs[i] != NULL; ++i) {

    if (x + strlen(dscs[i]->icon->title) >= width) {
      y += 5;
      x = 0;
      if (y >= height - 2 - 4) {
        morestart = i;
        break;
      }
    }
    CTK_WIDGET_SET_XPOS(dscs[i]->icon, x);
    CTK_WIDGET_SET_YPOS(dscs[i]->icon, y);
    CTK_WIDGET_ADD(&window, dscs[i]->icon);

    x += (unsigned char)strlen(dscs[i]->icon->title) + 2;
  }
  CTK_WIDGET_SET_YPOS(&autoexitbutton, height - 2);
  CTK_WIDGET_ADD(&window, &autoexitbutton);
  CTK_WIDGET_SET_YPOS(&autoexitlabel, height - 2);
  CTK_WIDGET_ADD(&window, &autoexitlabel);
  CTK_WIDGET_FOCUS(&window, &autoexitbutton);

  if (i != morestart) {
    CTK_WIDGET_SET_YPOS(&backbutton, height - 1);
    CTK_WIDGET_ADD(&window, &backbutton);
  } else {
    CTK_WIDGET_SET_YPOS(&morebutton, height - 1);
    CTK_WIDGET_ADD(&window, &morebutton);
  }
  CTK_WIDGET_SET_XPOS(&reloadbutton, width - 8);
  CTK_WIDGET_SET_YPOS(&reloadbutton, height - 1);
  CTK_WIDGET_ADD(&window, &reloadbutton);
}
/*-----------------------------------------------------------------------------------*/
static void quit(void) {
  unsigned char i;

  if (loading == LOADING_DIR) {
    cfs_closedir(&dir);
  }
  ctk_window_close(&window);
  for (i = 0; dscs[i] != NULL; ++i) {
    LOADER_UNLOAD_DSC(dscs[i]);
  }
  process_exit(&directory_process);
  LOADER_UNLOAD();
}
/*-----------------------------------------------------------------------------------*/
static void read_dirent(void) {
  static struct cfs_dirent dirent;
  static char message[40];

  if (loading == LOADING_DIR) {
    if (cfs_readdir(&dir, &dirent)) {
      cfs_closedir(&dir);
      loading = LOADING_DSC;
      filenameptr = 0;
    } else {
      strncpy(filenames[numfiles], dirent.name, FILENAMELEN);
      filenames[numfiles][FILENAMELEN] = '\0';
      ++numfiles;
      if (numfiles == MAX_NUMFILES) {
        cfs_closedir(&dir);
        loading = LOADING_DSC;
        filenameptr = 0;
        return;
      }
      strcpy(message, "Found \"");
      strcpy(message + 7, dirent.name);
      strcpy(message + 7 + strlen(dirent.name), "\"...");
      show_statustext(message);
    }
  }
}
/*-----------------------------------------------------------------------------------*/
static void load_dirent(void) {
  static char message[40];
  char *name;

  if (loading == LOADING_DSC) {
    if (filenameptr >= numfiles) {
      dscs[numfiles] = NULL;
      loading = 0;
      makewindow(0);
      show_statustext("Directory loaded");
      ctk_window_redraw(&window);
      return;
    }

    name = filenames[filenameptr];
    dscs[filenameptr] = LOADER_LOAD_DSC(name);

    /* Fallback for general non-.dsc files */
    if (dscs[filenameptr] == NULL) {
#if CTK_CONF_ICONS
      memset(&default_icons[filenameptr], 0, sizeof(struct ctk_icon));
      default_icons[filenameptr].type = CTK_WIDGET_ICON;
      default_icons[filenameptr].w = strlen(filenames[filenameptr]);
      if (default_icons[filenameptr].w < 3) {
        default_icons[filenameptr].w = 3;
      }
      default_icons[filenameptr].h = 4;
      default_icons[filenameptr].title = filenames[filenameptr];
#if CTK_CONF_ICON_BITMAPS
      default_icons[filenameptr].bitmap = NULL;
#endif
#if CTK_CONF_ICON_TEXTMAPS
      default_icons[filenameptr].textmap = file_textmap;
#endif
      default_dscs[filenameptr].icon = &default_icons[filenameptr];
#else
      default_dscs[filenameptr].icon = NULL;
#endif
      default_dscs[filenameptr].description = "Data File";
      default_dscs[filenameptr].prgname = "";
      dscs[filenameptr] = &default_dscs[filenameptr];
    }

    ++filenameptr;
    strcpy(message, "Loading \"");
    strcpy(message + 9, name);
    strcpy(message + 9 + strlen(name), "\"...");
    show_statustext(message);
  }
}
/*-----------------------------------------------------------------------------------*/
PROCESS_THREAD(directory_process, ev, data) {
  unsigned char i;

  PROCESS_BEGIN();

  width = ctk_draw_width() - 2;
  height = ctk_draw_height() - 2 - CTK_CONF_MENUS;

  ctk_window_new(&window, width, height, "Directory");

  makewindow(0);
  show_statustext("Loading directory...");
  startloading();

  ctk_window_open(&window);

  while (1) {
    PROCESS_WAIT_EVENT();
    if (ev == PROCESS_EVENT_CONTINUE) {
      read_dirent();
      load_dirent();
      if (loading != 0) {
        process_post(&directory_process, PROCESS_EVENT_CONTINUE, NULL);
      }
    } else if (ev == ctk_signal_widget_activate) {
      if (data == (process_data_t)&reloadbutton) {
        for (i = 0; dscs[i] != NULL; ++i) {
          LOADER_UNLOAD_DSC(dscs[i]);
          dscs[i] = NULL;
        }
        startloading();
        makewindow(0);
        ctk_window_open(&window);
      } else if (data == (process_data_t)&morebutton) {
        makewindow(morestart);
        ctk_window_open(&window);
      } else if (data == (process_data_t)&backbutton) {
        makewindow(0);
        ctk_window_open(&window);
      } else if (data == (process_data_t)&autoexitbutton) {
        autoexit = 1 - autoexit;
        if (autoexit == 1) {
          ctk_label_set_text(&autoexitlabel, autoexiton);
        } else {
          ctk_label_set_text(&autoexitlabel, autoexitoff);
        }
        CTK_WIDGET_REDRAW(&autoexitlabel);
      } else {
        for (i = 0; dscs[i] != NULL; ++i) {
          if (data == (process_data_t)(dscs[i]->icon)) {
            if (dscs[i]->prgname && strlen(dscs[i]->prgname) > 0) {
              program_handler_load(dscs[i]->prgname, NULL);
              if (autoexit) {
                ctk_window_close(&window);
                quit();
              }
            }
            break;
          }
        }
      }
    } else if (ev == ctk_signal_widget_select) {
      if (data == (process_data_t)&reloadbutton) {
        show_statustext("Reload directory");
      } else if (data == (process_data_t)&morebutton) {
        show_statustext("Show more files");
      } else if (data == (process_data_t)&backbutton) {
        show_statustext("Show first files");
      } else if (data == (process_data_t)&autoexitbutton) {
        show_statustext("Exit when loading program");
      } else {
        for (i = 0; dscs[i] != NULL; ++i) {
          if (data == (process_data_t)(dscs[i]->icon)) {
            show_statustext(dscs[i]->description);
            break;
          }
        }
      }
    } else if (ev == ctk_signal_window_close &&
               data == (process_data_t)&window) {
      quit();
    } else if (ev == PROCESS_EVENT_EXIT) {
      ctk_window_close(&window);
      quit();
    }
  }
  PROCESS_END();
}