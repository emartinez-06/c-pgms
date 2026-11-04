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
#include <stdio.h>  /* printf() */
#include <stdlib.h> /* exit MACROS */
#include <unistd.h> /* chdir(), getcwd() */

int main(int argc, char *argv[]) {
  const char *filename;
  char cwd[256];

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]", argv[0]);
    exit(EXIT_FAILURE);
  }

  filename = argv[1];
  if ((getcwd(cwd, 256)) == NULL) {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }

  printf("file: %s\n", filename);
  printf("cwd: %s\n", cwd);

  exit(EXIT_SUCCESS);
}
