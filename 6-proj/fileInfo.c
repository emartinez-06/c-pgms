/*
 * file: fileInfo.c
 * author: erick martinez
 * course: CSI 3336
 * assignment: project 6
 * due date: 10/25/2026
 *
 * date modified: 10/16/2026
 *  - created file, defined basic structs, I/O
 *
 *  This document will complete the requirements of project 6
 */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <unistd.h> /* read() and write() */
#include <sys/stat.h> /* struct stat */
#include <stdio.h>

/*
 * .st_size - size in bytes
 * .st_atime - the time of the last access
 * .st_mtime - the time of the last modification
 * .st_ctime - the time of the last change to the inode
 *
 *
 */

typedef struct FileInfo{
  char *path;
  struct stat info;
} FileInfo;

typedef struct Node {
  FileInfo file;
  struct Node *next;
} Node;

/*
 * main
 *
 * This functions is the main entry-point of the following C-program
 *
 * Parameters:
 *    fileone: the first file to perform actions on
 *    filetwo: the second file to perform actions on
 *                and compare to fileone
 *
 * Output:
 *    return: EXIT_SUCCESS on success 1 otherwise
 *    reference parameters: none 
 *    stream: none 
 */
int main(int argc, char *argv[]){
  struct stat stat_fileone;
  struct stat stat_filetwo;

  if(argc != 3){
    fprintf(stderr, "Usage: %s [file1] [file2]", argv[0]);
    return EXIT_FAILURE;
  }

  if(stat(argv[1], &stat_fileone) == -1 ||
     stat(argv[2], &stat_filetwo) == -1) {
        perror("stat");
        return EXIT_FAILURE;
      }

  stat(argv[1], &stat_fileone);
  stat(argv[2], &stat_filetwo);

  fprintf(stdout, "%ld\n", stat_fileone.st_size);
  fprintf(stdout, "%ld\n", stat_filetwo.st_size);

  return EXIT_SUCCESS;
}
