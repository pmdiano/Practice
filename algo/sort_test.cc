#include <vector>
#include <cstdio>
#include "sort.h"
#include "myutil.h"
using namespace std;

int main() {
    vector<int> A(20);
    for (int i = 0; i < A.size(); i++) {
        A[i] = i%15 + 1;
    }

    shuffle(&A[0], 0, A.size()-1);
    printf("Original: ");
    print_vec(A);

    quickSort(&A[0], 0, A.size()-1);
    printf("Quick sort: ");
    print_vec(A);

    shuffle(&A[0], 0, A.size()-1);
    printf("\nOriginal: ");
    print_vec(A);

    mergeSort(&A[0], 0, A.size()-1);
    printf("Merge sort: ");
    print_vec(A);    

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
