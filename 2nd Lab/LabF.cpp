#include <iostream>
#include <cstdlib>
#define int long long

int partition(int arr[], int left, int mid, int right) {
    int count = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;


    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            count += (n1 - i); 
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    delete[] leftArr;
    delete[] rightArr;
    return count;
}

int mergesort(int arr[], int left, int right) {
    int count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += mergesort(arr, left, mid);
        count += mergesort(arr, mid + 1, right);
        count += partition(arr, left, mid, right);
    }
    return count;
}

int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    srand(time(NULL));
    int count = mergesort(arr, 0, n - 1);
    std::cout << count << std::endl;
    
    return 0;
}