
#include <stdio.h>     /* fprintf() */
#include <stdlib.h>    /* EXIT_MACROS */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid() */
#include <unistd.h>    /* pipe() */

#define NUM_CHILDREN 5

int main(int argc, char *argv[]) {
  char *filename;

  pid_t w;
  pid_t c_pids[NUM_CHILDREN];
  int fds[2];

  int i, j;

  int rets[NUM_CHILDREN];

  for (i = 0; i < NUM_CHILDREN; i++) {
    pipe(fds);
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
      break;
    }
  }

  for (j = 0; j < NUM_CHILDREN; j++) {
    int status, count;
    w = waitpid(c_pids[j], &status, 0);

    if (w == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
      rets[j] = WEXITSTATUS(status);
    }
  }

  exit(EXIT_SUCCESS);
}
