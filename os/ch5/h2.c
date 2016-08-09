#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int
main(int argc, char* argv[])
{
    char buf[100];
    int file = open("./h2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    sprintf(buf, "hello world (pid:%d)\n", (int) getpid());
    write(file, buf, strlen(buf));

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        sprintf(buf, "hello from child (pid:%d)\n", (int) getpid());
        write(file, buf, strlen(buf));
    } else {
        int wc = waitpid(rc, NULL, 0);
        sprintf(buf, "hello from parent of %d (pid:%d)\n",
            rc, (int) getpid());
        write(file, buf, strlen(buf));
    }
    return 0;
}
