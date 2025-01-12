#include <iostream>
using namespace std;

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
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    InsertionSort(arr,n);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    delete [] arr;
    cout << endl;
}

// Insertion sort
// #include <iostream>
// using namespace std;

// void insertion_sort(long long a[], long long n){
//     for (long long  i = 1;i < n; i++){
//         // Lay ra phan tu x o chi so i
//         long long x = a[i];
//         long long  position = i - 1;
//         while ( (position >= 0) && (x < a[position]) ){
//             a [position +1] = a[position];
//             position--;
//         }
//         a[position + 1] = x;
//     }
// }
// int main() {
//     long long  n;
//     cin>>n;
//     long long* a = new long long[n];
//     for ( long long i=0;i < n;i++ ){
//         cin>>a[i];
//     }
//     insertion_sort(a,n);
//     for (long long  i = 0; i < n;i++){
//         cout<<a[i]<<" ";
//     }
//     return 0;
// }