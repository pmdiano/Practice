#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    printf("location of code  : %p\n", (void *) main);
    printf("location of heap  : %p\n", (void *) malloc(1));
    vector<int> *pv = new vector<int>(100000000);
    printf("location of vector: %p\n", (void *) pv);
    int x = 3;
    printf("location of stack : %p\n", (void *) &x);
    vector<int> v(100000000);
    printf("location of vector: %p\n", (void *) &v);
    return x;
}
