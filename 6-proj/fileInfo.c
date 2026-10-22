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
#include <sys/types.h>
#include <unistd.h> /* read() and write() */

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
  char buf[16];
  ssize_t n;
  int ord;
  int i;

  Node *head = NULL;
  Node *tail = NULL;

  for (i = 1; i < argc; i++) {
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
      p_error("memalloc failed\n");
      exit(EXIT_FAILURE);
    }

    node->file.path = argv[i];
    node->next = NULL;

    if (lstat(argv[i], &node->file.info) == -1) {
      p_error("lstat");
      free(node);
      exit(EXIT_FAILURE);
    }

    if (head == NULL) {
      head = node;
    } else {
      tail->next = node;
    }

    tail = node;
  }

  print("Choose your order: \n"
        "1. by size \n"
        "2. by access time \n"
        "3. by modified time \n"
        "4. by status change time \n");
  read(STDIN_FILENO, buf, sizeof(buf));
  ord = buf[0] - '0';

  if (ord < 1 || ord > 4) {
    p_error("invalid choice\n");
    exit(EXIT_FAILURE);
  }

  while (head != NULL) {
    Node *next = head->next;
    free(head);
    head = next;
  }

  exit(EXIT_SUCCESS);
}
