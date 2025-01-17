#include <iostream>
#include <cstdlib>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

long randompivot(long l, long r) {
    return l + rand() % (r - l + 1); 
}

long hoare(long arr[], long l, long r) {
    long pivotindex = randompivot(l, r);
    long pivot = arr[pivotindex];
    long i = l - 1;
    long j = r + 1;

    while (true) {
        do {
            j--;
        } while (arr[j] > pivot);

        do {
            i++;
        } while (arr[i] < pivot);

        if (i < j) {
            std::swap(arr[i], arr[j]);
        } else
            return j;
    }
}

void quicksort(long arr[], long l, long r) {
    if (l >= r)
        return;
    long p = hoare(arr, l, r);
    quicksort(arr, l, p);
    quicksort(arr, p + 1, r);
}

int main() {
    long n;
    std::cin >> n;
    long* arr = new long[n];

    for (long i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    srand(time(NULL));
    quicksort(arr,0,n-1);

    long* saveplace = new long[n];
    for (long i = 0; i < n; i++){
        saveplace[i] = 0;
    }
    long i = n - 1;
    long j = 0;
    while (i > 0){
        if (arr[i] == arr[i - 1]){
            saveplace[j] = arr[i];
            i -= 2;
            j++;
        }
        else if (arr[i] - 1 == arr[i - 1]){
            saveplace[j] = arr[i] - 1;
            i -= 2;
            j++;
        }
        else{
            i--;
        }
    }
    long sum = 0;

    for (long k = 0; k < n; k += 2){
        sum += saveplace[k] * saveplace[k + 1];
    }
    std::cout << sum;   
    return 0;
}