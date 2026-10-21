#include <stdio.h>  /* fsetpos(), fopen(), fclose() */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */

int main(int argc, char *argv[]) {
  char *filename = NULL;
  int num_chars;
  num_chars = 0;
  int ch;

  FILE *stream;

  switch (argc) {
  case 2:
    filename = argv[1];
    num_chars = 120;
    break;
  case 3:
    num_chars = atoi(argv[1]);
    if (num_chars < 0) {
      fprintf(stderr, "chracter count must be nonnegative\n");
      exit(EXIT_FAILURE);
    }
    filename = argv[2];
    break;
  default:
    fprintf(stderr, "Usage: %s [-num_chars] filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  stream = fopen(filename, "r");
  if (stream == NULL) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  if (fseek(stream, 0, SEEK_END) != 0) {
    perror("SEEK_END");
    fclose(stream);
    exit(EXIT_FAILURE);
  }
  long size;
  if ((size = ftell(stream)) == -1) {
    perror("ftell");
    fclose(stream);
    exit(EXIT_FAILURE);
  }
  if (num_chars > size) {
    num_chars = size;
  }

  if (fseek(stream, -num_chars, SEEK_CUR) != 0) {
    perror("SEEK_CUR");
    fclose(stream);
    exit(EXIT_FAILURE);
  }
  while (num_chars > 0 && (ch = fgetc(stream)) != EOF) {
    putchar(ch);
    num_chars--;
  }

  fclose(stream);
  return EXIT_SUCCESS;
}
