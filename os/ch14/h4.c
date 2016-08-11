#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int *data = (int*)malloc(100 * sizeof(int));
    free(data);
    printf("data after free: %d\n", data[20]);
    return 0;
}
