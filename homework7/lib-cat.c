/**
 * file: lib-cat.c
 * author: Erick Martinez
 * course: CSI 3336
 * professor: Prof. Aars
 * assignment: Homework 7, question 1
 * due date: 10/16/2026
 *
 * date modified: 10/15/2026
 *     - Created and completed the program in one session.
 *
 * This program copies one file to standard output using stdio.
 */

#include <stdio.h>

/**
 * main
 *
 * Copies the specified file to standard output using stdio.
 *
 * Parameters:
 *     argc: The number of command-line arguments, including the program name.
 *     argv: The argument strings; argv[1] specifies the input filename.
 *
 * Output:
 *     return: 0 on completion, or 1 for a detected error.
 *     reference parameters: none.
 *     stream: File contents to standard output; errors to standard error.
 */
int main(int argc, char *argv[]){
  int ch;
  FILE * fileptr;

  /* Require exactly one filename. */
  if(argc != 2){
    fprintf(stderr, "Usage: %s [filename] \n", argv[0]);
    return 1;
  }
  
  fileptr = fopen(argv[1], "r");
  if (fileptr == NULL){
    perror(argv[1]);
    return 1;
  }

  while((ch = fgetc(fileptr)) != EOF){
    putchar(ch);
  }

  fclose(fileptr);
  return 0;
}
