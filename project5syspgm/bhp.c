#ifndef bhp_c
#define bhp_c
/**
 * file: bhp.c 
 * author: erick martinez
 * course: csi 3336
 * assignment: project 5
 * due date: 10/11/2026
 *
 * date modified: 10/08/2026
 *    - read stdin
 *
 * date modified: 10/09/2026
 *    - create a dynamically allocated CmdList
 *    - ensured all edge cases were accounted for
 *
 * This C program reads from stdin a list of commands and assigns them objects in
 *  dynamically growing list to count occurences of said commands.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Count commands encountered in .bash_history. */
typedef struct CmdRec {
  char cmdName[13]; /* Null-terminated command name. */
  int cmdCount;    /* Command frequency. */
} CmdRec;

typedef struct CmdList {
  CmdRec *cmds;
  size_t capacity;
  size_t size;
} CmdList;

int grow(CmdList *list) {
  /* Increase capacity by 5. */
  size_t newCap = list->capacity + 5;
  CmdRec *bigger = malloc(sizeof(CmdRec) * newCap);

  if (bigger == NULL) {
    return 0;
  }

  for (size_t i = 0; i < list->size; i++) {
    bigger[i] = list->cmds[i];
  }

  free(list->cmds);
  list->cmds = bigger;
  list->capacity = newCap;
  return 1;
}

int proccessLine(CmdList *list, const char *line) {
  /* TODO: Extract the command name and update its record. */
  return 1;
}

int main(void) {
  CmdList list = {.cmds = NULL, .capacity = 1, .size = 0};
  list.cmds = malloc(sizeof(CmdRec) * list.capacity);

  if (list.cmds == NULL) {
    return 1;
  }

  char buf[256];
  char line[1024];
  ssize_t charsRead;
  size_t lineLen = 0;

  while ((charsRead = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
    for (ssize_t i = 0; i < charsRead; i++) {
      if (buf[i] == '\n') {
        line[lineLen] = '\0';
        printf("Got line: %s\n", line);
        proccessLine(&list, line);
        lineLen = 0;
      } else {
        if (lineLen >= sizeof(line) - 1) {
          fprintf(stderr, "Input line too long\n");
          free(list.cmds);
          return 1;
        }

        line[lineLen++] = buf[i];
      }
    }
  }

  if (charsRead < 0) {
    perror("read");
    free(list.cmds);
    return 1;
  }

  /* Handle the final line when it has no newline. */
  if (lineLen > 0) {
    line[lineLen] = '\0';
    printf("Got line: %s\n", line);
    proccessLine(&list, line);
  }

  free(list.cmds);
  return 0;
}

#endif
