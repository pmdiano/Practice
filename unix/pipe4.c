/* second pipe example from Haviland */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSGSIZE 64

char *msg1 = "hello #1";
char *msg2 = "hello #2";
char *msg3 = "hello #3";

int main()
{
    char inbuf[MSGSIZE];
    int p[2], j, pid;

    /* open pipe */

    if(pipe(p) == -1) {
        perror("pipe call error");
        exit(1);
    }

    switch(pid = fork()) {
    case -1:
        perror("error: fork call");
        exit(2);

    case 0:  /* if child then write down pipe */
        close(p[0]);  /* first close the read end of the pipe */
        if(dup2(p[1], 1) == -1 ) { /* stdout == write end of the pipe */
            perror( "dup2 failed" );
            _exit(1);
        }
        /* close(p[1]);*/
        printf("Child says:%s\n", msg1);
        printf("Child says:%s\n", msg2);
        printf("Child says:%s\n", msg3);
        break;

    default:   /* parent reads pipe */
        close(p[1]);  /* first close the write end of the pipe */
        if(dup2(p[0], 0 ) == -1 ) { /* stdin == read end of the pipe */
            perror( "dup2 failed" );
            _exit(1);
        }
        close(p[0]);  /* close the fd of read end of the pipe */

        while( scanf( "%s", inbuf ) != EOF ) {
            printf("Parent: %s\n", inbuf);
        }
        wait(NULL);
    }
    exit(0);
}
