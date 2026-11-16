
#include <stdio.h>     /* fprintf() */
#include <stdlib.h>    /* EXIT_MACROS */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid() */
#include <unistd.h>    /* pipe() */

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [filename] [num_children]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char *filename;
  int num_children;
  filename = argv[1];
  num_children = atoi(argv[2]);

  pid_t w;
  pid_t c_pids[num_children];
  int i, j;
  int fds[2];
  int rets[num_children];

  FILE *fp;
  int count, num;

  if ((fp = fopen(filename, "rb")) == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  count = 0;
  while (fread(&num, sizeof num, 1, fp) == 1) {
    count++;
  }
  fclose(fp);

  if (num_children > count) {
    fprintf(stderr,
            "Use a smaller num_children: %s [filename] [num_children]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < num_children; i++) {
    int sum;
    if (pipe(fds) == -1) {
      perror("pipe()");
      exit(EXIT_FAILURE);
    }
    c_pids[i] = fork();

    switch (c_pids[i]) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    case 0:
      /* child */
      return sum;
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
      rets[j] = WEXITSTATUS(status);
    }
  }

  exit(EXIT_SUCCESS);
}
