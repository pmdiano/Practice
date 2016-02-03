/**
 * Start 4 threads 1, 2, 3, 4. Thread 1's function is to output '1',
 * thread 2 output '2', etc. Now there are 4 files ABCD, initially
 * are all empty, and we want to use the 4 threads to output to the
 * 4 files such that they are:
 * 
 * A: 1 2 3 4 1 2 ...
 * B: 2 3 4 1 2 3 ...
 * C: 3 4 1 2 3 4 ...
 * D: 4 1 2 3 4 1 ...
 */

#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <vector>
using namespace std;

static const int N = 4;
static const int rounds = 100;

vector<ofstream> files(N);
vector<thread> threads(N);
condition_variable cv_ready, cv_write;
mutex mtx;
volatile int ready = 0;
volatile int go = 0;

void thread_func(int tid) {
  for (int i = 0; i < rounds; ++i) {
    unique_lock<mutex> lck(mtx);
    ++ready;
    cv_ready.notify_one();

    cv_write.wait(lck, [&]() -> bool {
      return go & (1 << tid);
    });

    go &= ~(1 << tid);
    lck.unlock();

    int fid = ((tid-i)%N+N)%N;
    files[fid] << tid+1;
  }
}

int main(void) {
  for (int i = 0; i < N; ++i) {
    string filename = "A.txt";
    filename[0] += i;
    files[i].open(filename);
    threads[i] = thread(thread_func, i);
  }

  for (int i = 0; i < rounds; ++i) {
    unique_lock<mutex> lock(mtx);
    cv_ready.wait(lock, [&]() -> bool {
      return ready == 4;
    });

    ready = 0;
    go = 0xF;
    cv_write.notify_all();
  }

  for (int i = 0; i < N; ++i) {
    threads[i].join();
  }

  for (int i = 0; i < N; ++i) {
    files[i].close();
  }

  return 0;
}
