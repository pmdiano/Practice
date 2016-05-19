#include <iostream>
#include "stack.h"
using namespace std;

int main(int argc, const char* argv[])
{
  try {
    Stack<int> S;
    for (int i = 1; i <= 7; ++i) {
      S.push(i);
    }

    while (!S.empty()) {
      cout << S.pop() << endl;
    }
    cout << S.pop() << endl;
    cout << S.top() << endl;

  } catch (exception& e) {
    printf("%s\n", e.what());
  }

  return 0;
}
