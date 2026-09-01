#include "cfs/cfs.h"
#include "contiki.h"
#include "ctk/ctk-draw.h"
#include "ctk/ctk.h"
#include "editor.h"
#include <stdint.h>
#include <string.h>

// All Official Upstream Standalone Applications
PROCESS_NAME(about_process);
PROCESS_NAME(calc_process);
PROCESS_NAME(directory_process);
PROCESS_NAME(processes_process);
PROCESS_NAME(program_handler_process);
PROCESS_NAME(gui_shell_process);

// Top Desktop Menus
static struct ctk_menu system_menu;
static struct ctk_menu apps_menu;

PROCESS(desktop_boot_process, "Desktop Boot");

struct process *const autostart_processes[] = {&desktop_boot_process, NULL};

// Populate CFS RAM Disk with sample files at startup
static void init_cfs_ram_files(void) {
  int fd;
  const char *readme = "Contiki OS on Bare-Metal RV32IM CPU!\nBuilt with "
                       "upstream Contiki & CTK.\n";
  const char *info =
      "Target: RV32IM @ 24MHz\nRAM: 256KB Unified\nVRAM: 320x200 RGB565\n";

  fd = cfs_open("readme.txt", CFS_WRITE);
  if (fd >= 0) {
    cfs_write(fd, readme, strlen(readme));
    cfs_close(fd);
  }

  fd = cfs_open("system.inf", CFS_WRITE);
  if (fd >= 0) {
    cfs_write(fd, info, strlen(info));
    cfs_close(fd);
  }
}

PROCESS_THREAD(desktop_boot_process, ev, data) {
  PROCESS_BEGIN();

  // 1. Preload RAM disk files
  init_cfs_ram_files();

  // 2. Build "Contiki" System Menu (Left side)
  ctk_menu_new(&system_menu, "  Contiki  ");
  ctk_menuitem_add(&system_menu, "About OS");
  ctk_menuitem_add(&system_menu, "Task Manager");
  ctk_menuitem_add(&system_menu, "File Manager");

  // 3. Build "Applications" Menu (Right side)
  ctk_menu_new(&apps_menu, "  Applications  ");
  ctk_menuitem_add(&apps_menu, "Command Shell");
  ctk_menuitem_add(&apps_menu, "Text Editor");
  ctk_menuitem_add(&apps_menu, "Calculator");
  ctk_menuitem_add(&apps_menu, "Program Launcher");

  // 4. Register menus (left-to-right)
  ctk_menu_add(&system_menu);
  ctk_menu_add(&apps_menu);

  // 5. Open About Contiki at boot
  process_start(&about_process, NULL);

  while (1) {
    PROCESS_WAIT_EVENT();

    if (ev == ctk_signal_menu_activate) {
      struct ctk_menu *m = (struct ctk_menu *)data;
      if (m == &system_menu) {
        if (m->active == 0)
          process_start(&about_process, NULL);
        else if (m->active == 1)
          process_start(&processes_process, NULL);
        else if (m->active == 2)
          process_start(&directory_process, NULL);
      } else if (m == &apps_menu) {
        if (m->active == 0)
          process_start(&gui_shell_process, NULL);
        else if (m->active == 1)
          process_start(&editor_process, NULL);
        else if (m->active == 2)
          process_start(&calc_process, NULL);
        else if (m->active == 3)
          process_start(&program_handler_process, NULL);
      }
    } else if (ev == ctk_signal_window_close) {
      ctk_window_close((struct ctk_window *)data);
    }
  }

  PROCESS_END();
}

static clock_time_t sys_ticks = 0;
clock_time_t clock_time(void) { return sys_ticks; }
unsigned long clock_seconds(void) { return sys_ticks / 1000; }

int main(void) {
  process_init();
  ctk_draw_init();

  process_start(&ctk_process, NULL);
  process_start(&desktop_boot_process, NULL);

  while (1) {
    sys_ticks++;
    process_run();
    etimer_request_poll();
  }

  return 0;
}