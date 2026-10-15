/**
 * file: syscalls-cat.c
 * author: Erick Martinez
 * course: CSI 3336
 * professor: Prof. Aars
 * assignment: Homework 7, question 2
 * due date: 10/16/2026
 *
 * date modified: 10/15/2026
 *     - Created and completed the program in one session.
 *
 * This program copies one file to standard output using system calls.
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/**
 * main
 *
 * Copies the specified file to standard output using system calls.
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
  char buf[4096];
  ssize_t charsRead;
  int fd;

  /* Require exactly one filename. */
  if(argc != 2){
    const char message[] = "Usage: syscalls-cat filename\n";
    write(STDERR_FILENO, message, sizeof(message) - 1);
    return 1;
  }

  fd = open(argv[1], O_RDONLY);
  if(fd == -1){
    perror(argv[1]);
    return 1;
  }


  while((charsRead = read(fd, buf, sizeof(buf))) > 0){
    ssize_t totalWritten;
    totalWritten = 0;

    /* A partial write leaves bytes to send from the current buffer. */
    while(totalWritten < charsRead){
      ssize_t written = write(
          STDOUT_FILENO,
          buf + totalWritten,
          charsRead - totalWritten
          );

      if(written <= 0){
        perror("write");
        close(fd);
        return 1;
      }
      totalWritten += written;
    }
  }

  if(charsRead == -1){
    perror("read");
    close(fd);
    return 1;
  }

  if(close(fd) == -1){
    perror("close");
    return 1;
  }

  return 0;
}
