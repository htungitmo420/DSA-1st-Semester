#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int total = 1 << n;
    for (int mask = 0; mask < total; mask++) {
        int code = mask ^ (mask >> 1);
        for (int j = n - 1; j >= 0; --j) {
            std::cout << ((code >> j) & 1);
        }
        std::cout << "\n";
    }
    return 0;
}
