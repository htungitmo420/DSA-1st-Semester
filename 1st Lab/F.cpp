#include <iostream>

int main() {
    long long j, k;
    std::cin >> j >> k;
    long long arr[60];
    arr[0] = 1;
    for (int i = 1; i < 60; i++) {
        arr[i] = arr[i-1]*2;
    }

    int count = 0;
    
    for (int a = 1; a <= 58; a++) {
        for (int b = 1; b <= 58; b++) {
            for (int c = 1; c <= 58; c++) {
                if (a+b+c<=60){
                long long sum =0;
                for (int i = 0; i < 60; i++) {
                    if (i < a) {
                        sum += arr[i];
                    } else if (i >= a + b && i < a + b + c) {
                        sum += arr[i];
                    }
                }
                if (j <= sum && sum <= k) {
                    count++;
                    }
                }
            }
        }
    }
    std::cout << count << std::endl;
    
    return 0;
}