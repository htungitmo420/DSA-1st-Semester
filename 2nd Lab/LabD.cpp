#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int randompivot(int l, int r) {
    return l + rand() % (r - l + 1);
}

int partition(int arr[], int l, int r) {
    int pivotIndex = randompivot(l, r);
    int pivot = arr[pivotIndex];
    int i = l - 1;
    int j = r + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            return j;
        }
    }
}


void quicksort(int arr[], int l, int r) {
    if (l < r) {
        int p = partition(arr, l, r);
        quicksort(arr, l, p);
        quicksort(arr, p + 1, r);
    } else {
        return;
    }
}

int main() {
    int n;
    cin >> n;

    int* b = new int[n];
    int* e = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> b[i] >> e[i];
    }
    srand(time(NULL));
    quicksort(b, 0, n - 1);
    quicksort(e, 0, n - 1);

    int total = 0;
    int begin = b[0];
    int end = e[0];

    for (int i = 1; i < n; i++) {
        if (b[i] <= end) {
            end = max(end, e[i]);
        } else {
            total += end - begin + 1;
            begin = b[i];
            end = e[i];
        }
    }

    total += end - begin + 1;
    cout << total << endl;
    delete[] b;
    delete[] e;
    return 0;
}