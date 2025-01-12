#include <iostream>
using namespace std;

int main() {
    int n,k;
    cin >> n >> k;

    int* arr = new int[n];
    for (int i =0; i < n; i++) {
        cin >> arr[i];
    }

    k = k % n;
    if (k<0)
    {
        k = k + n;
    }

    for (int i = 0; i < n; i++) {
        cout << arr[(i + n - k) % n] << " ";
    }

    return 0;
}