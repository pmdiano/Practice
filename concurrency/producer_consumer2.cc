/**
 * File:      producer_consumer.cc
 * Synopsis:  Producer-consumer pattern with multiple producers and multiple consumers
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
const int cargo_count = 80;
const int producer_num = 3;
const int consumer_num = 5;
volatile int produced = 0;
volatile int consumed = 0;

mutex mtx;
condition_variable cv_produce, cv_consume;
auto producing_duration = chrono::milliseconds(30);
auto consuming_duration = chrono::milliseconds(100);

void producer(int id) {
  unique_lock<mutex> lock(mtx);

  while (produced++ < cargo_count) {
    lock.unlock();
    this_thread::sleep_for(producing_duration);
    int cargo = rand() % 100;
    lock.lock();

    while (buffer.full()) {
      cv_produce.wait(lock);
    }

    buffer.push_back(cargo);
    printf("%s %d %s %d\n", FGRN("Producer"), id,  FGRN("produced cargo"), cargo);

    cv_consume.notify_one();
  }
}

void consumer(int id) {
  unique_lock<mutex> lock(mtx);

  while (consumed++ < cargo_count) {
    while (buffer.empty()) {
      cv_consume.wait(lock);
    }

    int cargo = buffer.front();
    buffer.pop_front();

    lock.unlock();
    this_thread::sleep_for(consuming_duration);
    lock.lock();

    printf("%s %d %s %d\n", FYEL("Consumer"), id, FYEL("consumed cargo"), cargo);
    cv_produce.notify_one();
  }
}

int main(void) {
  srand(time(nullptr));

  thread pth[producer_num];
  thread cth[consumer_num];

  for (int i = 0; i < producer_num; ++i) pth[i] = thread(producer, i);
  for (int i = 0; i < consumer_num; ++i) cth[i] = thread(consumer, i);

  for (auto &th : pth) th.join();
  for (auto &th : cth) th.join();

  return 0;
}
