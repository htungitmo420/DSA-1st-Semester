#include <iostream>

int main() {
    int n,k;
    std::cin >> n >> k;

    int* arr = new int[n];
    for (int i =0; i < n; i++) {
        std::cin >> arr[i];
    }

    k = k % n;
    if (k<0)
    {
        k = k + n;
    }

    for (int i = 0; i < n; i++) {
        std::cout << arr[(i + n - k) % n] << " ";
    }

    return 0;
}