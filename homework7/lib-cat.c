#include <stdio.h> /* for I/O */
/*
 * stdio.h predifines streams:
 * FILE *stdin - streams only buffered if not
 *                referred to an interactice device
 * FILE *stdout - streams only buffered if not
 *                referred to an interactice device
 * FILE *stderr - stream not fully buffered
 */
int main(int argc, char *argv[]){
  int ch;
  FILE * fileptr;
  
  fileptr = fopen(argv[1], "r");
  if (fileptr == NULL){
    perror(argv[1]);
    return 1;
  }

  while((ch = fgetc(fileptr)) != EOF){

  }

  fclose(fileptr);
  return 0;
}
