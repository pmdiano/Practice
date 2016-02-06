#include <cstdio>
#include <thread>
#include <atomic>
#include <vector>
using namespace std;

atomic<bool> ready(false);
atomic_flag winner = ATOMIC_FLAG_INIT;

void race(int id) {
  // This is we busy waiting
  while (!ready) {
    this_thread::yield();
  }

  // Also busy waiting
  while (winner.test_and_set()) {}

  printf("Thread %d\n", id);
  winner.clear();
}

int main(void) {
  int num = thread::hardware_concurrency() * 2;
  printf("We have %d threads\n", num);

  vector<thread> threads(num);
  for (int i = 0; i < num; ++i) {
    threads[i] = thread(race, i);
  }

  const int seconds = 10;
  printf("Waiting for %d seconds...\n", seconds);
  this_thread::sleep_for(chrono::seconds(seconds));
  ready = true;

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
