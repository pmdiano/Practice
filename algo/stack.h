/**
 * A simple stack implementation using array
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <new>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <stdexcept>

template<typename T>
class Stack {
  T* _buffer;
  uint32_t _size;
  uint32_t _capacity;
  const static uint32_t _SIZE0 = 100;

  void _ensureBuffer() {
    if (_capacity == 0) {
      _buffer = new (std::nothrow) T[_SIZE0];
      if (!_buffer) {
        throw std::bad_alloc();
      }
      _capacity = _SIZE0;
    } else if (_size == _capacity) {
      if (_capacity >> 31) {
        throw std::overflow_error("Stack overflow");
      }
      T* buffer2 = new (std::nothrow) T[_capacity * 2];
      if (!buffer2) {
        throw std::bad_alloc();
      }
      memcpy(buffer2, _buffer, _size * sizeof(T));
      delete[] _buffer;
      _buffer = buffer2;
      _capacity *= 2;
    }
  }

public:
  Stack() :
    _buffer(nullptr),
    _size(0),
    _capacity(0)
  {}

  ~Stack() {
    if (_buffer) {
      delete[] _buffer;
      _buffer = nullptr;
      _size = 0;
      _capacity = 0;
    }
  }

  void push(const T& item) {
    _ensureBuffer();
    _buffer[_size++] = item;
  }

  T& pop() {
    if (empty()) {
      throw std::underflow_error("Popping empty stack");
    }
    _size--;
    return _buffer[_size];
  }

  T& top() {
    if (empty()) {
      throw std::underflow_error("Toppong empty stack");
    }
    return _buffer[_size - 1];
  }

  uint32_t size() {
    return _size;
  }

  bool empty() {
    return _size == 0;
  }
};

#endif
