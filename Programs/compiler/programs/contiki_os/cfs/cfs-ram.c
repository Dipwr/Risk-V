/*
 * Multi-file RAM File System implementation for Contiki OS
 * Pre-populates default files at boot time for testing.
 */

#include "cfs/cfs.h"
#include <string.h>

#define MAX_FILES 8
#define MAX_FILENAME_LEN 32

#ifdef CFS_RAM_CONF_SIZE
#define CFS_RAM_SIZE CFS_RAM_CONF_SIZE
#else
#define CFS_RAM_SIZE 4096
#endif

struct ram_file {
  int in_use;
  char name[MAX_FILENAME_LEN];
  int size;
  int ptr;
  char data[CFS_RAM_SIZE / MAX_FILES];
};

static struct ram_file files[MAX_FILES];

struct cfs_ram_dir_state {
  int index;
};

/*---------------------------------------------------------------------------*/
void cfs_ram_init(void) {
  static int initialized = 0;
  if (initialized)
    return;
  initialized = 1;

  memset(files, 0, sizeof(files));

  /* Pre-populate test files so CFS is never empty on boot */
  int fd = cfs_open("readme.txt", CFS_WRITE);
  if (fd > 0) {
    cfs_write(fd, "Contiki OS running on RV32IM CPU.", 33);
    cfs_close(fd);
  }

  fd = cfs_open("system.inf", CFS_WRITE);
  if (fd > 0) {
    cfs_write(fd, "RAM CFS Drive OK\nMax Files: 8", 28);
    cfs_close(fd);
  }

  fd = cfs_open("test.txt", CFS_WRITE);
  if (fd > 0) {
    cfs_write(fd, "Hello World!", 12);
    cfs_close(fd);
  }
}
/*---------------------------------------------------------------------------*/
int cfs_open(const char *n, int f) {
  cfs_ram_init();
  if (!n)
    return -1;

  int slot = -1;
  for (int i = 0; i < MAX_FILES; i++) {
    if (files[i].in_use && strcmp(files[i].name, n) == 0) {
      slot = i;
      break;
    }
  }

  if (slot == -1 && (f & CFS_WRITE)) {
    for (int i = 0; i < MAX_FILES; i++) {
      if (!files[i].in_use) {
        slot = i;
        files[slot].in_use = 1;
        strncpy(files[slot].name, n, MAX_FILENAME_LEN - 1);
        files[slot].name[MAX_FILENAME_LEN - 1] = '\0';
        files[slot].size = 0;
        break;
      }
    }
  }

  if (slot == -1)
    return -1;

  if (f & CFS_READ) {
    files[slot].ptr = 0;
  }
  if (f & CFS_WRITE) {
    if (f & CFS_APPEND) {
      files[slot].ptr = files[slot].size;
    } else {
      files[slot].ptr = 0;
      files[slot].size = 0;
    }
  }

  return slot + 1;
}
/*---------------------------------------------------------------------------*/
void cfs_close(int f) {}
/*---------------------------------------------------------------------------*/
int cfs_read(int f, void *buf, unsigned int len) {
  int slot = f - 1;
  if (slot < 0 || slot >= MAX_FILES || !files[slot].in_use)
    return -1;

  struct ram_file *file = &files[slot];
  if (file->ptr >= file->size)
    return 0;

  if (file->ptr + len > file->size) {
    len = file->size - file->ptr;
  }

  memcpy(buf, &file->data[file->ptr], len);
  file->ptr += len;
  return len;
}
/*---------------------------------------------------------------------------*/
int cfs_write(int f, const void *buf, unsigned int len) {
  int slot = f - 1;
  if (slot < 0 || slot >= MAX_FILES || !files[slot].in_use)
    return -1;

  struct ram_file *file = &files[slot];
  int max_capacity = sizeof(file->data);

  if (file->ptr >= max_capacity)
    return 0;
  if (file->ptr + len > max_capacity) {
    len = max_capacity - file->ptr;
  }

  memcpy(&file->data[file->ptr], buf, len);
  file->ptr += len;
  if (file->ptr > file->size) {
    file->size = file->ptr;
  }
  return len;
}
/*---------------------------------------------------------------------------*/
cfs_offset_t cfs_seek(int f, cfs_offset_t o, int w) {
  int slot = f - 1;
  if (slot < 0 || slot >= MAX_FILES || !files[slot].in_use)
    return (cfs_offset_t)-1;

  struct ram_file *file = &files[slot];
  if (w == CFS_SEEK_SET) {
    if (o > file->size)
      o = file->size;
    file->ptr = o;
    return o;
  }
  return (cfs_offset_t)-1;
}
/*---------------------------------------------------------------------------*/
int cfs_remove(const char *name) {
  if (!name)
    return -1;
  for (int i = 0; i < MAX_FILES; i++) {
    if (files[i].in_use && strcmp(files[i].name, name) == 0) {
      files[i].in_use = 0;
      files[i].size = 0;
      files[i].ptr = 0;
      return 0;
    }
  }
  return -1;
}
/*---------------------------------------------------------------------------*/
int cfs_opendir(struct cfs_dir *p, const char *n) {
  cfs_ram_init();
  struct cfs_ram_dir_state *state = (struct cfs_ram_dir_state *)p;
  state->index = 0;
  return 0;
}
/*---------------------------------------------------------------------------*/
int cfs_readdir(struct cfs_dir *p, struct cfs_dirent *e) {
  struct cfs_ram_dir_state *state = (struct cfs_ram_dir_state *)p;

  while (state->index < MAX_FILES) {
    int i = state->index++;
    if (files[i].in_use) {
      strncpy(e->name, files[i].name, sizeof(e->name) - 1);
      e->name[sizeof(e->name) - 1] = '\0';
      e->size = files[i].size;
      return 0;
    }
  }

  return -1;
}
/*---------------------------------------------------------------------------*/
void cfs_closedir(struct cfs_dir *p) {}
/*---------------------------------------------------------------------------*/