
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *filename = NULL;
  int num_chars;
  num_chars = 0;

  switch (argc) {
  case 2:
    filename = argv[1];
    break;
  case 3:
    num_chars = atoi(argv[1]);
    filename = argv[2];
    break;
  default:
    fprintf(stderr, "Usage: %s [-num_chars] filename", argv[0]);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
