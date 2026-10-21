#include <stdio.h> /* fopen, fclose, fgetc */
#include <stdlib.h>
#include <unistd.h> /* getopt */

int main(int argc, char *argv[]) {
  /* getopt */
  int opt;

  /* std I/O */
  FILE *stream;
  char *filename = NULL;

  int lines;
  lines = 0;
  int ch;

  while ((opt = getopt(argc, argv, "tfoi:")) != -1) {
    switch (opt) {
    case 't':
      lines += 10;
      /* 10 lines added */
      break;
    case 'f':
      lines += 5;
      /* 5 lines added */
      break;
    case 'o':
      lines += 1;
      /* 1 line added */
      break;
    case 'i':
      filename = optarg;
      /* optarg */
      break;
    default:
      fprintf(stderr, "Usage: %s [-t] [-f] [-o] -i filename\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (filename == NULL) {
    fprintf(stderr, "Use -i [filename] \n");
    exit(EXIT_FAILURE);
  }

  stream = fopen(filename, "r");
  if (stream == NULL) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  while (lines > 0 && (ch = fgetc(stream)) != EOF) {
    putchar(ch);
    if (ch == '\n') {
      lines--;
    }
  }

  fclose(stream);
  return EXIT_SUCCESS;
}
