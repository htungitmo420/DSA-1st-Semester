#include <iostream>

int main(){
    int n;
    std::cin >> n;
    int* a = new int[n];
    int* sum = new int[n + 1];  
    sum[0] = 0;
    for (int i = 0; i < n ; i++){
        std::cin >> a[i];
        sum[i + 1] = sum[i] + a[i];
    }
    int index = -1;
    for (int i = 1; i < n ; i++){
        if (sum[i-1] == sum[n] - sum[i])
        {
            index = i-1;
            break;
        }
    }
    std::cout << index << std::endl;
    return 0;
}