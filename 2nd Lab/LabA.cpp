#include <iostream>

void InsertionSort(int arr[], int n) {
    int pos,x;
    for (int i = 1 ; i < n; i++) {
        x = arr[i];
        pos = i - 1;
        while ((pos >= 0) && (arr[pos] > x)) {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = x;
    }
}

int main(){
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    InsertionSort(arr,n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << "\n";
}