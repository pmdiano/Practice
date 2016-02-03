/**
 * Start some threads with ID A, B, C, ..., each thread will print
 * its ID for 10 times, and they print in turns. So the final output
 * should be ABCDEABCDE... (if 5 threads)
 */

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

static const int total = 7;
int now = -1;
int ready = 0;
mutex mtx;
condition_variable cv, cv_main;
vector<thread> threads(total);

void thread_func(int count, int idx, char msg) {
  while (count--) {
    unique_lock<mutex> lock(mtx);

    ++ready;
    cv_main.notify_one();

    cv.wait(lock, [&]() -> bool {
      return now == idx;
    });

    // Here we have only one CV and using the Pred as the signal. Another way
    // is to have the same number of CVs as threads, and each thread will
    // notify next thread's CV.
    // 
    // Which of the two approaches is preferred?

    cout << msg;
    ++now %= total;
    cv.notify_all();
  }
}

int main(void) {
  for (int i = 0; i < total; ++i) {
    threads[i] = thread(thread_func, 10, i, 'A'+i);
  }

  {
    // wait until all workers are ready
    unique_lock<mutex> lock(mtx);
    cv_main.wait(lock, [&]() -> bool {
      return ready == total;
    });

    // now they're all ready, fire
    now = 0;
    cv.notify_all();
  }

  for (auto &t : threads) {
    t.join();
  }

  cout << endl;
  return 0;
}
