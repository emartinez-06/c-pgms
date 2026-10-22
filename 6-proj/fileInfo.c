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
 *  - helper functions & nodes
 *
 * date modified: 10/22/2026
 *  - sort alogirthim
 *
 *  This document will complete the requirements of project 6
 */
#include <stddef.h>
#include <stdlib.h>    /* EXIT_SUCCESS */
#include <sys/stat.h>  /* struct stat */
#include <sys/types.h> /* MACROS */
#include <unistd.h>    /* read() and write() */

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

int cmp(const Node *a, const Node *b, int order) {
  /* returns non-zero if a should sort after b */
  int flag;
  flag = 0;
  switch (order) {
  case 1:
    flag = a->file.info.st_size < b->file.info.st_size;
    break;
  case 2:
    flag = a->file.info.st_atim.tv_sec < b->file.info.st_atim.tv_sec;
    break;
  case 3:
    flag = a->file.info.st_mtim.tv_sec < b->file.info.st_mtim.tv_sec;
    break;
  case 4:
    flag = a->file.info.st_ctim.tv_sec < b->file.info.st_ctim.tv_sec;
    break;
  default:
    p_error("cmp() failed\n");
    exit(EXIT_FAILURE);
  }
  return flag;
}

Node *sort(int order, Node *head) {
  /* bubble sort */
  int n = 0;
  int i, j;
  Node *p;
  for (p = head; p; p = p->next) {
    n++;
  }

  for (i = 0; i < n - 1; i++) {
    Node *curr = head;
    Node *prev = NULL;

    for (j = 0; j < n - 1; j++) {
      /* nonzero-true 0-false */
      if (cmp(curr, curr->next, order) > 0) {
        Node *temp = curr->next;
        curr->next = temp->next;
        temp->next = curr;

        if (prev == NULL) {
          head = temp;
        } else {
          prev->next = temp;
        }
        prev = temp;
      } else {
        prev = curr;
        curr = curr->next;
      }
    }
  }
  return head;
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
  int ord;
  int i;

  Node *head = NULL;
  Node *tail = NULL;
  Node *curr = NULL;

  for (i = 1; i < argc; i++) {
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
      p_error("memalloc failed\n");
      exit(EXIT_FAILURE);
    }

    node->file.path = argv[i];
    node->next = NULL;

    if (stat(argv[i], &node->file.info) == -1) {
      p_error("stat");
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
        "4. by status change time \n"
        ": ");
  if (read(STDIN_FILENO, buf, sizeof(buf)) == -1) {
    p_error("read");
    exit(EXIT_FAILURE);
  }
  ord = buf[0] - '0';

  switch (ord) {
  case 1:
    /* by st_size */
    head = sort(1, head);
    break;
  case 2:
    /* by st_atim */
    head = sort(2, head);
    break;
  case 3:
    /* by st_mtim */
    head = sort(3, head);
    break;
  case 4:
    /* by st_ctim */
    head = sort(4, head);
    break;
  default:
    p_error("invalid choice\n");
    exit(EXIT_FAILURE);
  }

  curr = head;
  while (curr) {
    print(curr->file.path);
    print(" ");
    curr = curr->next;
  }
  print("\n");

  while (head != NULL) {
    Node *next = head->next;
    free(head);
    head = next;
  }

  exit(EXIT_SUCCESS);
}
