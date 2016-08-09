#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    close(STDOUT_FILENO);
    open("./p5.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    // now exec "wc"
    char *myargs[3];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("p4.c");
    myargs[2] = NULL;
    execvp(myargs[0], myargs);

    printf("this shouldn't print out\n");
    return 0;
}
