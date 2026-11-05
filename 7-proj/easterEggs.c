/*
 * file: easterEggs.c
 * author: erick martinez
 * course: CSI 3336
 * assignment: project 7
 * due date: 11/08/2026
 *
 * date modified: 11/4/2026
 *  - recursie algo to sprawl + some basic color stubs
 *
 *
 */
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* exit MACROS */
#include <string.h>    /* strcmp() */
#include <sys/types.h> /* ino_t */
#include <sys/wait.h>  /* waitpid */
#include <unistd.h>    /* getcwd(), fork() */

typedef enum color { red, green, blue, yellow, orange } Color;

int sprawl(const char *path, const char *filename, char *paths[]) {
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
        if (sprawl(charPath, filename, paths) == -1) {
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

int countColors(char *path[], Color color) {
  int returnValue;
  returnValue = 0;
  /*
   * in returnVal
   * for path in paths:
   *  chdir(path)
   *  read file and count += to returnVal
   * */
  return returnValue;
}

int proccessColor(Color color, const char *path, const char *filename) {
  int occurences;
  char *paths = malloc(4096);

  switch (color) {
  case red:
    if (sprawl(path, filename, &paths) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }

    occurences = countColors(&paths, color);
    break;
  case green:
    if (sprawl(path, filename, &paths) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }

    occurences = countColors(&paths, color);
    break;
  case blue:
    if (sprawl(path, filename, &paths) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    occurences = countColors(&paths, color);
    break;
  case yellow:
    if (sprawl(path, filename, &paths) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    occurences = countColors(&paths, color);
    break;
  case orange:
    if (sprawl(path, filename, &paths) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    occurences = countColors(&paths, color);
    break;
  default:
    fprintf(stderr, "error: unknown color %d\n", (int)color);
    return -1;
  }

  free(paths);
  return occurences;
}

int main(int argc, char *argv[]) {
  char cwd[256];
  char *filename;
  Color *completedColors[5];

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
    int ret;

    switch (c_pids[i]) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    case 0:
      /* child */
      if ((ret = proccessColor(color, cwd, filename)) == -1) {
        fprintf(stderr, "error processing color %d\n", (int)color);
        exit(EXIT_FAILURE);
      }
      completedColors[color] + 1;
      return ret;
      break;
    default:
      /* parent */
      break;
    }
  }

  for (j = 0; j < num_children; j++) {
    w = waitpid(-1, NULL, 0);
    if (w == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    /* w holds the number of occurences for each color */
    printf("%u: %d\n", completedColors[0], w);
  }

  exit(EXIT_SUCCESS);
}
