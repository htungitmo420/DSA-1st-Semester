#include <iostream>

void AntiQuickSort(int n) {
    if (n == 1) {
        std::cout << "1" << "\n";
        return;
    }
    
    int* arr = new int[n];
    arr[0] = 1;
    arr[1] = 2;

    for (int i = 2; i < n; i++) {
        arr[i] = i + 1;
        int Pivot = arr[i / 2];
        arr[i / 2] = arr[i];
        arr[i] = Pivot;
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    AntiQuickSort(n);

    return 0;
}