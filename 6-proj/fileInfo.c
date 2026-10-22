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
 * date modified: 10/21/2026
 *  -
 *
 *  This document will complete the requirements of project 6
 */
#include <stddef.h>
#include <stdlib.h>   /* EXIT_SUCCESS */
#include <sys/stat.h> /* struct stat */
#include <unistd.h>   /* read() and write() */

/*
 * .st_size - size in bytes
 * .st_atime - the time of the last access
 * .st_mtime - the time of the last modification
 * .st_ctime - the time of the last change to the inode
 *
 *
 */

typedef struct FileInfo {
  char *path;
  struct stat info;
} FileInfo;

typedef struct Node {
  FileInfo file;
  struct Node *next;
} Node;

size_t str_len(const char *s) {
  size_t len;
  len = 0;

  while (s[len] != '\0') {
    len++;
  }

  return len;
}

void p_error(const char *s) {
  size_t len;
  len = str_len(s);
  write(STDERR_FILENO, s, len);
}
void print(const char *s) {
  size_t len;
  len = str_len(s);
  write(STDOUT_FILENO, s, len);
}

void print_num(unsigned int n) {
  char buf[16];
  int i = sizeof(buf);

  if (n == 0)
    buf[--i] = '0';
  while (n > 0) {
    buf[--i] = '0' + (n % 10);
    n /= 10;
  }
  write(STDOUT_FILENO, buf + i, sizeof(buf - i));
}

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
int main(int argc, char *argv[]) {
  struct stat sb1;
  struct stat sb2;
  int buf[4096];

  if (argc != 3) {
    p_error("Usage: ");
    p_error(argv[0]);
    p_error(" [file1] [file2]\n");
    exit(EXIT_FAILURE);
  }

  if (lstat(argv[1], &sb1) == -1 || lstat(argv[2], &sb2) == -1) {
    p_error("lstat");
    exit(EXIT_FAILURE);
  }

  print_num((unsigned int)sb1.st_ino);
  print("\n");
  print_num((unsigned int)sb2.st_ino);
  print("\n");

  exit(EXIT_SUCCESS);
}
