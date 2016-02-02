/**
 * Worker thread loop 5 times, then main thread loop 20 times
 * Repeat this process for 10 times.
 */
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
using namespace std;

int worker_count = 0;
int main_count = 0;
int loop_count = 10;

mutex mtx;
condition_variable cv_main, cv_worker;

bool isWorker = true;
bool worker_turn() { return isWorker; }
bool main_turn() { return !isWorker; }
void switch_to_worker() { isWorker = true; }
void switch_to_main() { isWorker = false; }

void worker(void) {
  while (loop_count) {
    for (int i = 0; i < 5; ++i) {
      cout << "Worker thread loop #" << ++worker_count << endl;
    }

    switch_to_main();
    cv_main.notify_one();

    unique_lock<mutex> lck(mtx);
    cv_worker.wait(lck, worker_turn);
  }
}

int main(void) {
  thread tworker = thread(worker);

  while (loop_count) {
    unique_lock<mutex> lck(mtx);
    cv_main.wait(lck, main_turn);

    for (int i = 0; i < 20; ++i) {
      cout << "Main thread loop #" << ++main_count << endl;
    }
    --loop_count;

    switch_to_worker();
    cv_worker.notify_one();
  }

  tworker.join();
  return 0;
}
