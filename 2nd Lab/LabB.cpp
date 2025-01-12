#include <iostream>
#include <cstdlib> //rand()
#include <ctime> //time()
using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int RandomPivot(int l, int r) { //random pivot [l;r]
    return l + rand() % (r - l + 1);
}

int Partition(int arr[], int l, int r) { //hoare
    int PivotIndex = RandomPivot(l, r);
    int Pivot = arr[PivotIndex];
    int i = l - 1;
    int j = r + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < Pivot);

        do {
            j--;
        } while (arr[j] > Pivot);

        if (i < j) {
            swap(arr[i], arr[j]);
        } else 
        return j;
    }
}

void QuickSort(int arr[], int l, int r) {
    if (l < r) {
        int p = Partition(arr, l, r);
        QuickSort(arr, l, p);
        QuickSort(arr, p + 1, r);
    }
}

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    srand(time(NULL));
    QuickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    delete [] arr;
    return 0;
}