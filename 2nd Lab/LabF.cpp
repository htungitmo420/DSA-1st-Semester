#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long partition(long arr[], long left, long mid, long right) {
    long count = 0;
    long n1 = mid - left + 1;
    long n2 = right - mid;


    long* leftArr = new long[n1];
    long* rightArr = new long[n2];

    for (long i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (long i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    long i = 0, j = 0, k = left;
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

long mergesort(long arr[], long left, long right) {
    long count = 0;
    if (left < right) {
        long mid = left + (right - left) / 2;
        count += mergesort(arr, left, mid);
        count += mergesort(arr, mid + 1, right);
        count += partition(arr, left, mid, right);
    }
    return count;
}

int main() {
    long n;
    cin >> n;
    long* arr = new long[n];
    for (long i = 0; i < n; i++) {
        cin >> arr[i];
    }

    srand(time(NULL));
    long count = mergesort(arr, 0, n - 1);
    cout << count << endl;

    delete[] arr;
    return 0;
}