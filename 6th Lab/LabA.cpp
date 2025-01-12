#include <iostream>

struct Heap {
    int n;
    int* arr;
    Heap(int size) : n(size) {
        arr = new int[n];
    }

    bool isHeap() {
        for (int i = 1; i <= n; i++) {
            if (2 * i <= n && arr[i-1] > arr[2*i-1]) {
                return false;
            }
            if (2* i + 1 <= n && arr[i-1] > arr[2*i]) {
                return false;
            }
         }
         return true;
    }
};

int main() {
    int n;
    std::cin >> n;
    Heap heap(n);
    for (int i = 0; i < n; i++) {
        std::cin >> heap.arr[i];
    }
    if (heap.isHeap()) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}