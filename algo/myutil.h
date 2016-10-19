#ifndef __MYUTIL_H__
#define __MYUTIL_H__

#include <cstdlib>
#include <utility>

template<typename T>
void shuffle(T* A, int p, int r) {
    for (int i = r; i > p; i--) {
        int j = rand() % (i-p+1);
        std::swap(A[i], A[j]);
    }
}

void print_vec(const std::vector<int>& vec) {
    if (vec.empty()) {
        printf("[]\n");
        return;
    }
    printf("[%d", vec[0]);
    for (int i = 1; i < vec.size(); i++) {
        printf(", %d", vec[i]);
    }
    printf("]\n");
}

void print_vec2d(const std::vector<std::vector<int>>& vec2d) {
    for (const auto& vec : vec2d) {
        print_vec(vec);
    }
}

#endif
