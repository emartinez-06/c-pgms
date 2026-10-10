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
 *    - added checks for allocation failures and long command names
 *
 * date modified: 10/10/2026
 *    - documented functions and command parsing
 *    - re-did stdin reading to use fgetc() instead of read()
 *
 * This program reads command names from standard input and counts their
 * occurrences in a dynamically growing array. It prints each command name
 * and its frequency to standard output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CmdRec {
  char cmdName[13]; /* Null-terminated command name. */
  int cmdCount;    /* Command frequency. */
} CmdRec;

typedef struct CmdList {
  CmdRec *cmds;     /* Points to the allocated command records. */
  size_t capacity; /* Stores the number of records the array can hold. */
  size_t size;     /* Stores the number of records currently in use. */
} CmdList;

/**
 * grow
 *
 * Expands the command array by five records, preserving existing records.
 * If allocation fails, the original array remains unchanged.
 *
 * Parameters:
 *     list: the command list whose capacity will be increased.
 *
 * Output:
 *     return: 1 on success, or 0 if allocation fails.
 *     reference parameters: updates the array pointer and capacity in *list.
 *     stream: none.
 */
int grow(CmdList *list) {
  size_t newCap = list->capacity + 5;
  CmdRec *bigger = malloc(sizeof(CmdRec) * newCap);
  size_t i;

  if (bigger == NULL) {
    return 0;
  }

  for (i = 0; i < list->size; i++) {
    bigger[i] = list->cmds[i];
  }

  free(list->cmds);
  list->cmds = bigger;
  list->capacity = newCap;
  return 1;
}

/**
 * proccessLine
 *
 * Counts the first word in the supplied string as a command. Empty strings
 * and command names longer than 12 characters do not change the counts.
 *
 * Parameters:
 *     list: the command list to search and update.
 *     line: a null-terminated string containing the command to process.
 *
 * Output:
 *     return: 1 if counted or skipped, or 0 if array growth fails.
 *     reference parameters: updates records, size, and possibly capacity
 *         and the array pointer in *list.
 *     stream: writes a diagnostic to stderr for names over 12 characters.
 */
int proccessLine(CmdList *list, const char *line) {
  char command[14];
  size_t i;

  /* Read one extra character to detect names longer than 12 characters. */
  if(sscanf(line, "%13s", command) != 1){
    return 1; 
  }

  /* Skip names that cannot fit in a command record. */
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


/**
 * main
 *
 * Reads commands from standard input and prints their execution counts.
 * Input parsing uses spaces to separate command names from arguments.
 *
 * Parameters:
 *     none.
 *
 * Output:
 *     return: 0 on success, or 1 on allocation or input failure.
 *     reference parameters: none.
 *     stream: reads stdin, writes the summary to stdout, and writes input
 *         and processing diagnostics to stderr.
 */
int main(void) {
  CmdList list = {NULL, 1, 0};
  char command[14];
  int ch;
  int commandDone = 0;
  size_t commandLen = 0;
  size_t i;

  list.cmds = malloc(sizeof(CmdRec) * list.capacity);

  if (list.cmds == NULL) {
    return 1;
  }

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
          /* Keep a thirteenth character so long names can be rejected. */
          command[commandLen++] = (char) ch;
        }
      }
    }

  if (ferror(stdin)) {
    perror("read");
    free(list.cmds);
    return 1;
  }

  /* Handle the final line when it has no newline. */
  if (commandLen > 0) {
    command[commandLen] = '\0';
    if(proccessLine(&list, command) == 0){
          fprintf(stderr, "Failed to process command\n");
          free(list.cmds);
          return 1;
        }
  }
  
  for(i = 0; i < list.size; i++){
    printf("%-12s %4d\n",
        list.cmds[i].cmdName,
      list.cmds[i].cmdCount);
  }

  free(list.cmds);
  return 0;
}

