
#include <inttypes.h>
#include <stdio.h>     /* fprintf() */
#include <stdlib.h>    /* EXIT_MACROS */
#include <string.h>    /* strinlen() */
#include <sys/stat.h>  /* stat() */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid() */
#include <unistd.h>    /* pipe(), read(), write() */

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [filename] [num_children]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char *filename;
  char buffer[256];
  int base, extra, next, count, i, j, fds[2], num_children, psum;
  struct stat file_info;

  filename = argv[1];
  sscanf(argv[2], "%d", &num_children);
  count = stat(filename, &file_info);

  pid_t c_pids[num_children], w;

  if (num_children > count) {
    fprintf(stderr,
            "Use a smaller num_children: %s [filename] [num_children]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  base = count / num_children;
  extra = count % num_children;
  next = 0, psum = 0;

  for (i = 0; i < num_children; i++) {
    int id, n, m;
    if (pipe(fds) == -1) {
      perror("pipe()");
      exit(EXIT_FAILURE);
    }
    /* indicies calculations */
    n = next;
    m = n + base;
    if (i < extra) {
      m++;
    }
    next = m;

    id = c_pids[i] = fork();
    if (id == 0) {
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
