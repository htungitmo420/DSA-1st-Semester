#include <iostream>
using namespace std;

void AntiQuickSort(int n) {
    if (n == 1) {
        cout << "1" << endl;
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
        cout << arr[i] << " ";
    }
}

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    AntiQuickSort(n);
    delete[] arr;
    return 0;
}