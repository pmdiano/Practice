#ifndef __SORT_H__
#define __SORT_H__

#include <climits>
#include <cstdlib>
#include <cstring>
#include <utility>

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

#endif