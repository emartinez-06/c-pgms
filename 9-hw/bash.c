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

  cpid = fork();
  switch (cpid) {
  case -1:
    perror("fork");
    return EXIT_FAILURE;
  case 0:
    execvp(argv[1], argv + 1);
    break;
  default:
    /* parent process */
    w = waitpid(cpid, $wstatus, WUNTRACED | WCONTINUED);
    break;
  }
  if (WIFEXITED(wstatus)) {
    fprintf(stdin, WEXITSTATUS(wstatus));
  } else if (WIFSIGNALED(wstatus)) {
    perror(WTERMSIG(wstatus));
  }

  return EXIT_SUCCESS;
}
