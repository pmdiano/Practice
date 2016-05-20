#include <cstdio>
#include "queue.h"
using namespace std;

int main(int argc, const char* argv[])
{
  try {
    Queue<int> Q;
    for (int i = 0; i < 6; ++i)
      Q.enqueue(i);
    for (int i = 0; i < 3; ++i)
      printf("size = %d, dequeue = %d\n", Q.size(), Q.dequeue());
    for (int i = 6; i < 25; ++i)
      Q.enqueue(i);
    for (int i = 0; i < 3; ++i)
      printf("size = %d, front = %d\n", Q.size(), Q.front());
    while (!Q.empty())
      printf("size = %d, dequeue = %d\n", Q.size(), Q.dequeue());

    printf("size = %d, dequeue = %d\n", Q.size(), Q.dequeue());

  } catch (exception& e) {
    printf("%s\n", e.what());
  }

  return 0;
}
