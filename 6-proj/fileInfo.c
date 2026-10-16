#include <stdlib.h>
#include <stdio.h>

typedef struct stat {

}stat; 

typedef struct FileInfo{
  char *path;
  struct stat info;
} FileInfo;

typedef struct Node {
  FileInfo file;
  struct Node *next;
} Node;

int main(int argc, char *argv[]){
  

  return EXIT_SUCCESS;
}
