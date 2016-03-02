#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

int main(int argc, char **argv)
{
  printf("--beginning of program\n");

  int counter = 0;
  int total = 20;
  pid_t pid = fork();

  if (pid == 0) {
    // child process
    int i = 0; 
    for (; i < total; ++i) {
      printf("child process: counter=%d\n", ++counter);
    }
  } else if (pid > 0) {
    // parent process
    int j = 0;
    for (; j < total; ++j) {
      printf("parent process: counter=%d\n", ++counter);
    }
  } else {
    // fork failed
    printf("fork() failed!\n");
    return 1;
  }

  printf("--end of program--\n");

  return 0;
}
