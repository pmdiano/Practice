/**
 * Problem: http://blog.csdn.net/morewindows/article/details/7442333
 */
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <cstdio>
using namespace std;

const int THREAD_NUM = 10;
volatile int g_num = 0;

bool gotit = false;
mutex mtx;
condition_variable cv;

void thread_func(void *pData) {
  unique_lock<mutex> lck(mtx);
  int data = *((int*)pData);
  gotit = true;
  cv.notify_one();

  // do some work
  lck.unlock();
  this_thread::sleep_for(chrono::milliseconds(50));
  lck.lock();

  int num = ++g_num;

  // do some more work - in pracice, you shouldn't sleep while locked
  this_thread::sleep_for(chrono::milliseconds(0));

  printf("Thread id = %d, global = %d\n", data, num);
}

int main(void) {
  int tid = 0;
  thread threads[THREAD_NUM];
  for (auto &t : threads) {
    t = thread(thread_func, &tid);

    unique_lock<mutex> lck(mtx);
    while (!gotit) cv.wait(lck);
    ++tid;
    gotit = false;
  }

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
