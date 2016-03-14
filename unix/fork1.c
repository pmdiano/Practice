#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_children(int n) {
    for (int i = 0; i < n; ++i) {
        switch (fork()) {
        case -1:
            printf("error, fork returned -1\n");
            return;
        case 0:
            printf("Child process %d\n", getpid());
            sleep(10);
            return;
        default:
            break;
        }
    }
    sleep(10);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fork_children(2);
    } else {
        fork_children(atoi(argv[1]));
    }
    return 0;
}
