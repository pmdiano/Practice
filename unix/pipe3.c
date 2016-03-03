#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main(int argc, char *argv[]) 
{
    int p[2]; 
    int i, pid, status; 
    char buffer[20]; 
    pipe(p);                        /* setting up the pipe   */ 

    if ((pid = fork()) == 0) {      /* in child */
        close(p[1]);                /* child closes p[1]     */ 
        while ((i = read(p[0], buffer, 8)) != 0) {
            buffer[i] = '\0';       /* string terminator     */ 
            printf("%d chars :%s: received by child\n", i, buffer); 
        }

        close(p[0]);
        _exit(0);                   /* child terminates      */ 
    } 

    /* in parent */ 
    close(p[0]);
    /* parent writes p[1]    */ 
    write(p[1], "Hello there, from me?extra", sizeof("Hello there, from me?")); 
    write(p[1], "How are you? - Ercal", sizeof("How are you? - Ercal")); 

    close(p[1]);                    /* finished writing p[1] */ 

    while (wait(&status) != pid);   /* waiting for pid       */ 
    if (status == 0)  printf("child finished\n"); 
    else printf("child failed\n"); 
    return(0); 
}
