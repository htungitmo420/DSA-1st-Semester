#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int random_pivot(int left, int right) {
    return left + rand() % (right - left + 1);
}

int partition(int* arr, int left, int right) {
    int pivot_value = arr[left];  
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot_value);

        do {
            j--;
        } while (arr[j] > pivot_value);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

void quickselect(int* arr, int left, int right, int k) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        if (pivot >= k) {
            quickselect(arr, left, pivot, k);  
        } else {
            quickselect(arr, pivot + 1, right, k); 
        }
    }
}

int main() {
    int n, k, A, B, C, a1, a2; //a1 = i-2, a2 = i-1
    cin >> n >> k;
    cin >> A >> B >> C >> a1 >> a2;
    int* arr = new int[n];
    arr[0] = a1;
    arr[1] = a2;
    for (int i = 2; i < n; ++i) {
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }

    srand(time(NULL));
    quickselect(arr, 0, n - 1, n - k);

    int result = 0;
    for (int i = n - k; i < n; ++i) {
        result ^= arr[i];
    }
    cout << result << endl;

    return 0;
}