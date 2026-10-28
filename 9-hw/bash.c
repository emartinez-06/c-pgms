/*
 * file: bash.c
 * author: Erick Martinez
 * course: CSI 3336
 * assignment: homework 9
 * due date: 10/30/2026
 *
 * date modified: 10/27/2026
 *  created file and used execlp
 */
#include <stdio.h>    /* perror */
#include <stdlib.h>   /* return MACROS */
#include <sys/wait.h> /* waitpid() */
#include <unistd.h>   /* execvp(), fork() */

int main(int argc, char *argv[]) {
  pid_t cpid, w;
  int wstatus;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s command [arguments...]\n", argv[0]);
    return EXIT_FAILURE;
  }

  cpid = fork();
  switch (cpid) {
  case -1:
    perror("fork");
    return EXIT_FAILURE;
  case 0:
    execvp(argv[1], argv + 1);
    perror("execvp");
    return EXIT_FAILURE;
  default:
    /* parent process */
    w = waitpid(cpid, &wstatus, 0);
    if (w == -1) {
      perror("waitpid");
      return EXIT_FAILURE;
    }
    if (WIFEXITED(wstatus)) {
      return WEXITSTATUS(wstatus);
    }
    if (WIFSIGNALED(wstatus)) {
      return WTERMSIG(wstatus);
    }
    return EXIT_FAILURE;
  }
}
