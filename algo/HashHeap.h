/**
 * A max/min heap that supports erase by value
 */
#ifndef _HASHHEAP_H_
#define _HASHHEAP_H_

#include <vector>
#include <unordered_map>
#include <algorithm>

enum class HeapType {
  minheap,
  maxheap
};

template<typename T>
class HashHeap {
  struct Node {
    int id;
    int count;
    Node(int i, int c) : id(i), count(c) {}
    Node() {}
  };

  int count;
  HeapType type;
  std::vector<T> heap;
  std::unordered_map<T, Node> hash;

  int parent(int i) {return (i-1) / 2;}
  int lson(int i) {return 2*i+1;}
  int rson(int i) {return 2*i+2;}

  bool comp_less(const T &lhs, const T &rhs) {
    if (type == HeapType::maxheap) {
      return lhs < rhs;
    } else {
      return rhs < lhs;
    }
  }

  void _swap(int i, int j) {
    std::swap(hash[heap[i]].id, hash[heap[j]].id);
    std::swap(heap[i], heap[j]);
  }

  void siftUp(int i) {
    while (parent(i) >= 0 && comp_less(heap[parent(i)], heap[i])) {
      _swap(i, parent(i));
      i = parent(i);
    }
  }

  void siftDown(int i) {
    int j = lson(i);
    while (j < heap.size()) {
      if (rson(i) < heap.size() && comp_less(heap[j], heap[rson(i)])) {
        j = rson(i);
      }
      if (comp_less(heap[j], heap[i])) {
        break;
      } else {
        _swap(i, j);
        i = j;
        j = lson(i);
      }
    }
  }

public:
  HashHeap(HeapType t) : type(t), count(0) {}

  int size() {return count;}
  bool empty() {return size() == 0;}

  void push(T x) {
    if (hash.find(x) != hash.end()) {
      ++hash[x].count;
    } else {
      heap.push_back(x);
      hash[x] = Node(heap.size() - 1, 1);
      siftUp(heap.size() - 1);
    }
    ++count;
  }

  void pop() {
    erase(top());
  }

  T top() {return heap[0];}

  void erase(T x) {
    if (--hash[x].count == 0) {
      int i = hash[x].id;
      _swap(i, heap.size() - 1);

      heap.pop_back();
      hash.erase(x);

      if (parent(i) >= 0 && comp_less(heap[parent(i)], heap[i])) {
        siftUp(i);
      } else {
        siftDown(i);
      }
    }

    --count;
  }
};

#endif
