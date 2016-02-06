#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <cstdio>
using namespace std;

atomic<long> g_userCount(0);
static const int num_threads = 50;

void user_login(void) {
  this_thread::sleep_for(chrono::milliseconds(100));
  ++g_userCount;
  this_thread::sleep_for(chrono::milliseconds(50));
}

int main(void) {
  int loop = 20;

  while (loop--) {
    g_userCount = 0;

    vector<thread> threads(num_threads);
    for_each(threads.begin(), threads.end(), [](thread &t){
      t = thread(user_login);
    });

    for_each(threads.begin(), threads.end(), [](thread &t){
      t.join();
    });

    printf("User count is %ld\n", g_userCount.load());
  }

  return 0;
}
