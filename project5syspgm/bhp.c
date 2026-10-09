#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

size_t strlen(char const* str){
  char const* p;
  for (p = str; *p; ++p);
  return p - str;

}

/* struct used to kepp a count of commands encountered in .bash_history */
typedef struct CmdRec{
  char cmdName[13]; /* null terminated name of comamnd */
  int cmdCount; /* frequ of commands encountered */
} CmdRec;

typedef struct CmdList{
  struct CmdRec *cmds;
  size_t capacity;
  size_t size;
} CmdList;

void* grow(*CmdList list){
  /* increase size by 5 */
  size_t newCap = list->capacity + 5;
  CmdRec *bigger = malloc(sizeof(CmdRec) * newCap);
  size_t i;

  if(bigger == NULL){
    return 0;
  }
  for(i = 0; i < list->size; i++){
    bigger[i] = list->cmds[i];
  }
  free(list->cmds);
  list->cmds = bigger;
  list->capacity = newCap;

  return 1;
}

int main(){
  CmdList list = { .cmds = NULL, .capacity = 1, .size = 0};
  list.cmds = malloc(sizeof(CmdRec) * list.capacity);

  char buf[256];
  ssize_t n = read(STDIN_FILENO, buf, sizeof(buf) - 1);

  int i;

  if(n > 0){
    buf[n] = '\0';
    for(i = 0; i < n; i++){
      if(list.size == list.capacity){
        grow(&list);
      }
      list.cmds[i].cmdName=buf[n];
      if(buf[n] == '\n' && n != buff - 1){ /* dont take last \n*/ 
        list.cmds.cmdCount++;
      }
      list.size++;
    }
    printf("%s%-12", buf);
  }


  return 0;
}



  /*
  char const* str="hello";
  size_t size = strlen(str);
  int fd = 1;
  
  write(fd, "hello\n", 6);


  char buf[3 * sizeof(size_t)];
  size_t pos = sizeof(buf);
  size_t n = size;

  do{
    buf[--pos] = '0' + n % 10;
    n /= 10;
  } while (n != 0);

  write(fd, buf + pos, sizeof(buf) - pos);
  write(fd, "\n", 1);
*/
