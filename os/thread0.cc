#include <thread>
#include <cstdio>
#include <cstdlib>

#define NUMBER_OF_THREADS 10

void print_hello_world(int tid)
{
    printf("Hello World. Greetings from thread %d\n", tid);
}

int main(int argc, char *argv[])
{
    std::thread threads[NUMBER_OF_THREADS];
    int i;

    for (i=0; i<NUMBER_OF_THREADS; ++i) {
        printf("Main here. Creating thread %d\n", i);
        threads[i] = std::thread(print_hello_world, i);
    }

    printf("Main exiting\n");
    exit(0);
}
