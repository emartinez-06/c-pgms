/**
 * file: head.c
 * author: Erick Martinez
 * course: CSI 3336
 * instructor: Prof. Aars
 * assignment: Homework 8
 * date created: October 21, 2026
 *
 * date modified: October 21, 2026
 *     - File created, implemented, and completed on the same date.
 *
 * Prints the requested number of lines from the beginning of a file.
 */

#include <stdio.h> /* fopen, fclose, fgetc */
#include <stdlib.h>
#include <unistd.h> /* getopt */

/**
 * main
 *
 * Prints the requested number of lines from the beginning of a file.
 *
 * Parameters:
 *     argc: The number of command-line arguments.
 *     argv: Command-line arguments containing -t, -f, -o, and -i filename.
 *
 * Output:
 *     return: EXIT_SUCCESS on success or EXIT_FAILURE on error.
 *     reference parameters: none.
 *     stream: Writes the selected lines to stdout and error messages to stderr.
 */
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
