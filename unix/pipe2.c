#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 32

char *msg1 = "hello #1";
char *msg2 = "hello #2";
char *msg3 = "hello #3";

int main(int argc, char *argv[]) {
    char inbuf[MSGSIZE];
    int p[2], j, pid;

    if (pipe(p) == -1) {
        perror("pipe call error");
        exit(1);
    }

    switch(pid = fork()) {
    case -1:
        perror("error: fork call");
        exit(2);

    case 0:
        close(p[0]);
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
        break;

    default:
        close(p[1]);
        for (j=0; j<3; ++j) {
            read(p[0], inbuf, MSGSIZE);
            printf("Parent: %s\n", inbuf);
        }
        wait(NULL);
    }

    return 0;
}
