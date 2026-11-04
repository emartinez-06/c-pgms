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
#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* exit MACROS */
#include <string.h>    /* strcmp() */
#include <sys/types.h> /* ino_t */
#include <unistd.h>    /* getcwd() */

int main(int argc, char *argv[]) {
  DIR *dp;
  struct dirent *entry;
  char cwd[256];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (getcwd(cwd, 256) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  if ((dp = opendir(cwd)) == NULL) {
    fprintf(stderr, "cannot opendir: %s\n", cwd);
    exit(EXIT_FAILURE);
  }

  while ((entry = readdir(dp)) != NULL) {
    if (entry == NULL) {
      perror("readdir");
      exit(EXIT_FAILURE);
    }

    if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name)) {
      printf("filename: %s\n", entry->d_name);
    }
  }

  closedir(dp);
  exit(EXIT_SUCCESS);
}
