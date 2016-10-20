#ifndef __SORT_H__
#define __SORT_H__

#include <climits>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <utility>

template<typename T>
void insertionSort(T* A, int p, int r) {
    for (int i = p+1; i <= r; i++) {
        T x = A[i];
        int j = i;
        for (; j-1 >= 0 && A[j-1] > x; j--) {
            A[j] = A[j-1];
        }
        A[j] = x;
    }
}

template<typename T>
void bubbleSort(T* A, int p, int r) {
    for (int i = p+1; i <= r; i++) {
        for (int j = r; j >= i; j--) {
            if (A[j-1] > A[j]) {
                std::swap(A[j-1], A[j]);
            }
        }
    }
}

template<typename T>
int partition(T* A, int p, int r) {
    T x = A[r];
    int i = p-1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            std::swap(A[++i], A[j]);
        }
    }
    std::swap(A[++i], A[r]);
    return i;
}

template<typename T>
void quickSort(T* A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q-1);
        quickSort(A, q+1, r);
    }
}

template<typename T>
std::pair<int, int> partition3(T* A, int p, int r) {
    T x = A[r];
    int i = p-1, k = r+1, j = p;
    while (j < k) {
        if (A[j] < x) {
            std::swap(A[++i], A[j++]);
        }
        else if (A[j] > x) {
            std::swap(A[--k], A[j]);
        }
        else {
            j++;
        }
    }
    return {i+1, k-1};
}

template<typename T>
T quickSelect(T* A, int p, int r, int k) {
    if (k <= 0 || k > r-p+1) {
        return INT_MAX;
    }

    int q = partition(A, p, r);
    int left = q-p+1;
    if (k == left) {
        return A[q];
    } else if (k < left) {
        return quickSelect(A, p, q-1, k);
    } else {
        return quickSelect(A, q+1, r, k-left);
    }
}

template<typename T>
void merge(T* A, int p, int q, int r) {
    T* B = (T*)malloc((r-p+1) * sizeof(T));
    memcpy(B, A+p, (r-p+1) * sizeof(T));
    int i = 0, j = q+1-p, k = p;
    while (i <= q-p && j <= r-p) {
        if (B[i] <= B[j]) {
            A[k++] = B[i++];
        }
        else {
            A[k++] = B[j++];
        }
    }
    while (i <= q-p) A[k++] = B[i++];
    while (j <= r-p) A[k++] = B[j++];
    free(B);
}

template<typename T>
void mergeSort(T* A, int p, int r) {
    if (p < r) {
        int q = (p+r)/2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }
}

template<typename T, class Cmp>
class Heap {
    T* data;
    int capacity;
    int size;
    bool hasOwnData;
    Cmp cmp;

    inline int parent(int i) {
        return (i-1) / 2;
    }

    inline int lson(int i) {
        return 2*i+1;
    }

    inline int rson(int i) {
        return 2*i+2;
    }

    void siftUp(int i) {
        for (;;) {
            int j = parent(i);
            if (j < 0 || !cmp(data[j], data[i])) {
                break;
            }
            std::swap(data[j], data[i]);
            i = j;
        }
    }

    void siftDown(int i) {
        for (;;) {
            int j = lson(i);
            if (rson(i) < size && cmp(data[j], data[rson(i)])) {
                j = rson(i);
            }
            if (j >= size || !cmp(data[i], data[j])) {
                break;
            }
            std::swap(data[i], data[j]);
            i = j;
        }
    }

public:
    Heap(T* A, int p, int r)
        : data(A+p)
        , capacity(r-p+1)
        , size(r-p+1)
        , cmp(Cmp())
        , hasOwnData(false) {
        for (int i = size/2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }

    Heap()
        : capacity(100)
        , size(0)
        , cmp(Cmp())
        , hasOwnData(true) {
        data = (T*)malloc(capacity*sizeof(T));
    }

    ~Heap() {
        if (hasOwnData) {
            free(data);
        }
    }

    T pop() {
        std::swap(data[0], data[--size]);
        siftDown(0);
        return data[size];
    }

    T top() {
        return data[0];
    }

    void push(T x) {
        if (size == capacity) {
            data = (T*)realloc(data, 2*capacity*sizeof(T));
            capacity *= 2;
        }
        data[size++] = x;
        siftUp(size-1);
    }

    bool empty() {
        return size == 0;
    }
};

template<typename T>
void heapSort(T* A, int p, int r) {
    Heap<T, std::less<T>> heap(A, p, r);
    while (!heap.empty()) {
        heap.pop();
    }
}

#endif