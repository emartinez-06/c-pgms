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
 *  a dynamically growing list to count occurences of said commands.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char command[14];
  size_t i;

  /* skips whitespace & assings values(returns) */
  if(sscanf(line, "%13s", command) != 1){
    return 1; 
  }

  /* fails to process commands greater than 12 */
  if(strlen(command) > 12){
    fprintf(stderr, "Command name > 12: %s\n", line);
    return 1;
  }

  for(i = 0; i < list->size; i++){
    if(strcmp(list->cmds[i].cmdName, command) == 0){
      list->cmds[i].cmdCount++;
      return 1;
    }
  }
      if(list->size == list->capacity){
        if(!grow(list)){
          return 0;
        }
      }

      strncpy(list->cmds[list->size].cmdName, command, 12);
      list->cmds[list->size].cmdName[12] = '\0';
      list->cmds[list->size].cmdCount = 1;
      list->size++;

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
        if(proccessLine(&list, line) == 0){
          fprintf(stderr, "Failed to process command\n");
          free(list.cmds);
          return 1;
        }
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
    if(proccessLine(&list, line) == 0){
          fprintf(stderr, "Failed to process command\n");
          free(list.cmds);
          return 1;
        }
  }
  
  size_t i;
  for(i = 0; i < list.size; i++){
    printf("%-12s %4d\n",
        list.cmds[i].cmdName,
      list.cmds[i].cmdCount);
  }

  free(list.cmds);
  return 0;
}

