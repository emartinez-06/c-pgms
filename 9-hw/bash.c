#include <stdlib.h> /* return MACROS */
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *cmd = argv[1];
  char *arg1 = "Hello!";

  execlp(argv[1], argv[1], arg1, NULL);
  return EXIT_SUCCESS;
}
