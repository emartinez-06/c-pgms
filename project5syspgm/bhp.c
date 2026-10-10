/*
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

#include <stdio.h> /* for fgetc() */
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strncpy(), strcmp() */

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

  char command[14];
  int ch;
  int commandDone = 0; /* no bools! */
  size_t commandLen = 0;


  while ((ch = fgetc(stdin)) != EOF) {
      if(ch == '\n'){
        command[commandLen] = '\0';

        if(proccessLine(&list, command) == 0){
          fprintf(stderr, "Failed to process command\n");
          free(list.cmds);
          return 1;
        }

        commandLen = 0;
        commandDone = 0;
      } else if(!commandDone){
        if (ch == ' ') {
          if(commandLen > 0){
            commandDone = 1;
          }
        } else if(commandLen < sizeof(command) - 1){
          command[commandLen++] = (char) ch;
        }
      }
    }

  if (ch < 0) {
    perror("read");
    free(list.cmds);
    return 1;
  }

  /* Handle the final line when it has no newline. */
  if (commandLen > 0) {
    command[commandLen] = '\0';
    if(proccessLine(&list, command)){
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

