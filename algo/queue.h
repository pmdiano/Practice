/**
 * A simple queue implementation using array
 */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <new>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <stdexcept>

template <typename T>
class Queue {
  T* _buffer;
  uint32_t _head;
  uint32_t _tail;
  uint32_t _len;
  const static uint32_t _LEN0 = 10;

  bool _full() {
    return size() + 1 >= _len;
  }

  void _ensureBuffer() {
    if (_len == 0) {
      _buffer = new (std::nothrow) T[_LEN0];
      if (!_buffer) {
        throw std::bad_alloc();
      }

      _len = _LEN0;
      _head = 0;
      _tail = 0;
    } else if (_full()) {
      if (_len >> 31) {
        throw std::overflow_error("Queue overflow");
      }

      T* buffer2 = new (std::nothrow) T[_len * 2];
      if (!buffer2) {
        throw std::bad_alloc();
      }

      if (_head <= _tail) {
        memcpy(buffer2, _buffer + _head, size() * sizeof(T));
      } else {
        memcpy(buffer2, _buffer + _head, (_len - _head) * sizeof(T));
        memcpy(buffer2 + (_len - _head), _buffer, _tail * sizeof(T));
      }

      delete[] _buffer;
      _buffer = buffer2;
      _tail = size();
      _head = 0;
      _len *= 2;
    }
  }

public:
  Queue() :
    _buffer(nullptr),
    _head(0),
    _tail(0),
    _len(0)
  {}

  ~Queue() {
    if (_buffer) {
      delete[] _buffer;
      _buffer = nullptr;
      _head = 0;
      _tail = 0;
      _len = 0;
    }
  }

  void enqueue(const T& item) {
    _ensureBuffer();

    _buffer[_tail++] = item;
    if (_tail == _len) {
      _tail = 0;
    }
  }

  T& dequeue() {
    if (empty()) {
      throw std::underflow_error("Dequeuing empty queue");
    }

    T& ret = _buffer[_head++];
    if (_head == _len) {
      _head = 0;
    }

    return ret;
  }

  T& front() {
    if (empty()) {
      throw std::underflow_error("Getting front of empty queue");
    }

    return _buffer[_head];
  }

  uint32_t size() {
    if (_head <= _tail)
      return (_tail - _head);
    else
      return _len - _head + _tail;
  }

  bool empty() {
    return _head == _tail;
  }
};

#endif
