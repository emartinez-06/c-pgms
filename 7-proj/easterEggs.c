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

int countColors(const char *path, Color color) {
  /* These parameters will be used when the counting logic is implemented. */
  (void)path;
  (void)color;
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
int create_file_path(char *charPath, size_t size, const char *currpath,
                     const char *filename) {
  int n;
  if ((n = snprintf(charPath, size, "%s/%s", currpath, filename)) < 0 ||
      (size_t)n >= size) {

    fprintf(stderr, "could not build dirpath\n");
    return -1;
  }
  return 0;
}

int sprawl(const char *path, const char *filename, Color color) {
  DIR *dp;
  struct dirent *entry;
  int occurences;
  occurences = 0;

  if ((dp = opendir(path)) == NULL) {
    fprintf(stderr, "cannot opendir: %s\n", path);
    return -1;
  }

  while ((entry = readdir(dp)) != NULL) {

    if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0) {

      if (entry->d_type == DT_REG) {
        int count;
        char filepath[512];
        create_file_path(filepath, 512, path, entry->d_name);

        if ((count = countColors(filepath, color)) == -1) {
          fprintf(stderr, "counting error on file %s and color %d", filepath,
                  (int)color);
          return -1;
        }
        occurences += count;
      } else if (entry->d_type == DT_DIR) {
        char dirpath[512];
        create_file_path(dirpath, 512, path, entry->d_name);
        if (sprawl(dirpath, filename, color) == -1) {
          closedir(dp);
          fprintf(stderr, "recurse error\n");
          return -1;
        }
      } else if (entry->d_type == DT_UNKNOWN) {
        fprintf(stderr, "error unknown file type(%u) continuing...\n",
                (unsigned int)entry->d_type);
      }
    }
  }
  closedir(dp);
  return 0;
}

int proccessColor(Color color, const char *path, const char *filename) {
  int occurences;

  switch (color) {
  case red:
    if ((occurences = sprawl(path, filename, red)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case green:
    if ((occurences = sprawl(path, filename, green)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case blue:
    if ((occurences = sprawl(path, filename, blue)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case yellow:
    if ((occurences = sprawl(path, filename, yellow)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  case orange:
    if ((occurences = sprawl(path, filename, orange)) == -1) {
      fprintf(stderr, "error\n");
      return -1;
    }
    break;
  default:
    fprintf(stderr, "error: unknown color %d\n", (int)color);
    return -1;
  }

  return occurences;
}

int main(int argc, char *argv[]) {
  char cwd[256];
  char *filename;
  char *colors[5] = {"red", "green", "blue", "yellow", "orange"};

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
      return ret;
      break;
    default:
      /* parent */
      break;
    }
  }

  for (j = 0; j < num_children; j++) {
    int status, count;
    w = waitpid(c_pids[j], &status, 0);
    if (w == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
      count = WEXITSTATUS(status);
      printf("%s: %d\n", colors[j], (int)count);
    }
  }

  exit(EXIT_SUCCESS);
}
