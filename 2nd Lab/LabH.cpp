#include <iostream>
#include <cstdlib>


void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void quicksort(int arr[], int l, int r) { 
    if (l >= r) return;
    int pivot = arr[l + (r-l) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j) {
                swap(arr[i],arr[j]);
                i++;
                j--;
            }
        }
        if (l < j)
            quicksort(arr, l, j);
        if (r > i)
            quicksort(arr, i, r);
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];

    for (int i = 0;i < n; i++) {
        std::cin >> arr[i];
        arr[i] = arr[i] + i; 
    }

    srand(time(NULL));
    quicksort(arr, 0, n - 1);
    for (int i = 0;i < n; i++) {
        arr[i] = arr[i] - i;
    }
    bool quicksorted = true;
    for (int i = 0;i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            quicksorted = false;
            break;
        }
    }
    if (quicksorted) {
        for (int i = 0;i < n; i++) {
            std::cout << arr[i] << " ";
        }
    } else {
        std::cout << ":(";
    }
    return 0;
}
