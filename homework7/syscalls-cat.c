#include <unistd.h>

int main(int argc, char *argv[]){
  char buf[4096];
  ssize_t charsRead;
  int fd;

  if(argc != 2){
    const char message[] = "Usage: syscalls-cat filename\n";
    write(STDERR_FILENO, message, sizeof(message) - 1);
    return 1;
  }

  fd = open(argv[1], O_RDONLY);
  if(fd == -1){
    perror(argv[1]);
    return 1;
  }


  while((charsRead = read(fd, buf, sizeof(buf))) > 0){
    ssize_t totalWritten;
    totalWritten = 0;

    while(totalWritten < charsRead){
      ssize_t written = write(
          STDOUT_FILENO,
          buf + totalWritten,
          charsRead - totalWritten
          );
      totalWritten += written;
    }
  }

  if(charsRead == -1){
    perror("read");
    close(fd);
    return 1;
  }

  if(close(fd) == -1){
    perror("close");
    return 1;
  }

  return 0;
}


