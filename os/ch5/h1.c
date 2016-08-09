#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char* argv[])
{
    int x = 100;
    printf("x = %d (pid:%d)\n", x, (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("x = %d, child (pid:%d)\n", x, (int) getpid());
        x = 200;
        printf("x = %d, child (pid:%d)\n", x, (int) getpid());
    } else {
        int wc = waitpid(rc, NULL, 0);
        printf("x = %d, parent of %d (wc:%d) (pid:%d)\n",
            x, rc, wc, (int) getpid());
    }
    return 0;
}
