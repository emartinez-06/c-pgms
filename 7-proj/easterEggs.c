/*
 * file: easterEggs.c
 * author: erick martinez
 * course: CSI 3336
 * assignment: project 7
 * due date: 11/08/2026
 *
 * date modified: 11/4/2026
 *  -
 *
 *
 */
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* exit MACROS */
#include <string.h>    /* strcmp() */
#include <sys/types.h> /* ino_t */
#include <unistd.h>    /* getcwd() */

int sprawl(const char *path) {
  DIR *dp;
  struct dirent *entry;
  int n;

  if ((dp = opendir(path)) == NULL) {
    fprintf(stderr, "cannot opendir: %s\n", path);
    return -1;
  }

  while ((entry = readdir(dp)) != NULL) {

    if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0) {

      if (entry->d_type == DT_REG) {
        printf("reg: %s\n", entry->d_name);
      } else if (entry->d_type == DT_DIR) {
        printf("dir: %s\n", entry->d_name);
        char charPath[512];
        if ((n = snprintf(charPath, sizeof charPath, "%s/%s", path,
                          entry->d_name)) < 0 ||
            (size_t)n >= sizeof charPath) {
          fprintf(stderr, "could not build dirpath\n");
          closedir(dp);
          return -1;
        }
        if (sprawl(charPath) == -1) {
          closedir(dp);
          fprintf(stderr, "recurse error\n");
          return -1;
        }
      } else if (entry->d_type == DT_UNKNOWN) {
        fprintf(stderr, "error unknown file type(%u) continuing...\n",
                (unsigned int)entry->d_type);
        printf("unknown: %s\n", entry->d_name);
      }
    }
  }
  closedir(dp);
  return 0;
}

int main(int argc, char *argv[]) {
  char cwd[256];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (getcwd(cwd, 256) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  if (sprawl(cwd) == -1) {
    fprintf(stderr, "error\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
