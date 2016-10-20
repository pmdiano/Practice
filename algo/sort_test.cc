#include <vector>
#include <cstdio>
#include "sort.h"
#include "myutil.h"
using namespace std;

template<typename T>
void testSort(vector<int>& A, void (*pfn)(T*, int, int), const char* name) {
    shuffle(&A[0], 0, A.size() - 1);
    printf("Original: ");
    print_vec(A);

    pfn(&A[0], 0, A.size()-1);
    printf("%s: ", name);
    print_vec(A);
}

int main() {
    vector<int> A(20);
    for (int i = 0; i < (int)A.size(); i++) {
        A[i] = i%15 + 1;
    }

    testSort<int>(A, bubbleSort, "Bubble sort"); printf("\n");
    testSort<int>(A, insertionSort, "Insertion sort"); printf("\n");
    testSort<int>(A, quickSort, "Quick sort"); printf("\n");
    testSort<int>(A, mergeSort, "Merge sort"); printf("\n");
    testSort<int>(A, heapSort, "Heap sort"); printf("\n");

    shuffle(&A[0], 0, A.size()-1);
    printf("\nOriginal: ");
    print_vec(A);
    printf("%dth element is %d\n", 1, quickSelect(&A[0], 0, A.size()-1, 1));
    printf("%dth element is %d\n", 5, quickSelect(&A[0], 0, A.size()-1, 5));
    printf("%dth element is %d\n", 20, quickSelect(&A[0], 0, A.size()-1, 20));

    vector<int> B({1, 4, 2, 2, 6, 5, 7, 2, 4, 4, 3});
    printf("\nOriginal: "); print_vec(B);
    auto p = partition3(&B[0], 0, B.size() - 1);
    printf("After partiton3: "); print_vec(B);
    printf("Equal range: [%d, %d]\n", p.first, p.second);

    return 0;
}
