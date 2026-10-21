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
  struct stat sb1;
  struct stat sb2;
  int buf[4096];

  if(argc != 3){
    fprintf(stderr, "Usage: %s [file1] [file2]", argv[0]);
    exit(EXIT_FAILURE);
  }

  if(lstat(argv[1], &sb1) == -1 ||
     lstat(argv[2], &sb2) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
      }

  write()

  exit(EXIT_SUCCESS);
}
