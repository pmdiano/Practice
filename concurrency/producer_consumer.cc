/**
 * File:      producer_consumer.cc
 * Synopsis:  Producer-consumer pattern with single producer and single consumer
 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "../include/util/colors.h"
using namespace std;

template <typename T>
class Buffer : public std::deque<T> {
  int buffer_size;
public:
  Buffer(int n = 10) : buffer_size(n)
  {
  }

  bool full() {
    return deque<T>::size() >= buffer_size;
  }
};

Buffer<int> buffer;
const int buffer_size = 10;
const int cargo_count = 50;

mutex mtx;
condition_variable cv_produce, cv_consume;
auto producing_duration = chrono::milliseconds(30);
auto consuming_duration = chrono::milliseconds(100);

void producer(void) {
  unique_lock<mutex> lock(mtx);

  for (int i = 0; i < cargo_count; ++i) {
    lock.unlock();
    this_thread::sleep_for(producing_duration);
    int cargo = rand() % 100;
    lock.lock();

    // It seems that the follwoing two are equivalent, but the first version
    // is more intuitive and easier to read.
    // From cplusplus.com:
    // If pred is specified (2), the function only blocks if pred returns false,
    // and notifications can only unblock the thread when it becomes true (which
    // is specially useful to check against spurious wake-up calls). This
    // version (2) behaves as if implemented as:
    //      while (!pred()) wait(lck);
    while (buffer.full()) {
      cv_produce.wait(lock);
    }
    // cv_produce.wait(lock, [&]{
    //   return !buffer.full();
    // });

    buffer.push_back(cargo);
    printf("%s %d\n", FGRN("Producer produced cargo "), cargo);

    cv_consume.notify_one();
  }
}

void consumer(void) {
  unique_lock<mutex> lock(mtx);

  for (int i = 0; i < cargo_count; ++i) {
    while (buffer.empty()) {
      cv_consume.wait(lock);
    }

    int cargo = buffer.front();
    buffer.pop_front();

    lock.unlock();
    this_thread::sleep_for(consuming_duration);
    lock.lock();

    printf("%s %d\n", FYEL("Consumer consumed cargo "), cargo);
    cv_produce.notify_one();
  }
}

int main(void) {
  srand(time(nullptr));

  thread pth = thread(producer), cth = thread(consumer);
  pth.join();
  cth.join();

  return 0;
}
