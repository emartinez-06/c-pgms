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
#include <unistd.h>    /* getcwd(), fork() */

typedef enum color { red, green, blue, yellow, orange } Color;

int sprawl(const char *path, const char *filename) {
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
        if (sprawl(charPath, filename) == -1) {
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
  char *filename;

  int i, num_children, j;
  num_children = 5;
  pid_t w;
  pid_t c_pids[num_children];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  filename = argv[1];

  if (getcwd(cwd, 256) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < num_children; i++) {
    Color color;
    color = i;
    c_pids[i] = fork();

    switch (c_pids[i]) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    case 0:
      /* child */

      break;
    default:
      /* parent */
    }
  }

  if (sprawl(cwd, filename) == -1) {
    fprintf(stderr, "error\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
