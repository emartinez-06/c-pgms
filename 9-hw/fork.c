/*
 * file: fork.c
 * author: Erick Martinez
 * course: CSI 3336
 * assignment: homework 9
 * due date: 10/30/2026
 *
 * date modified: 10/27/2026
 *  created file and used execlp
 */
#include <stdio.h>    /* perror() fprintf() */
#include <stdlib.h>   /* return MACROS */
#include <sys/wait.h> /* waitpid() */
#include <time.h>     /* time() */
#include <unistd.h>   /* fork() */

int main(void) {
  int num_children, i, j;
  num_children = 5;

  pid_t w;
  pid_t c_pids[num_children];

  time_t tloc;
  struct tm *tm;
  char buffer[100];

  for (i = 0; i < num_children; i++) {
    c_pids[i] = fork();

    switch (c_pids[i]) {
    case -1:
      perror("fork");
      return EXIT_FAILURE;
    case 0:
      /* child process */
      if (time(&tloc) == -1) {
        perror("time");
        return EXIT_FAILURE;
      }
      tm = localtime(&tloc);
      if (tm == NULL) {
        perror("localtime");
        return EXIT_FAILURE;
      }
      strftime(buffer, sizeof(buffer), "%A, %m/%d/%Y %H:%M:%S", tm);
      puts(buffer);
      return EXIT_SUCCESS;
    default:
      /* parent process */
    }
  }

  /* printf might happen before child finishes since everything is concurrent */
  printf("Waiting for children...\n");
  for (j = 0; j < num_children; j++) {
    w = waitpid(-1, NULL, 0);
    if (w == -1) {
      perror("waitpid");
      return EXIT_FAILURE;
    }
  }
  printf("Done\n");

  return EXIT_SUCCESS;
}
