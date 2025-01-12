#include <iostream>
#include <vector>

const int MOD = 1000000007;

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<long long>> current(k, std::vector<long long>(2, 0));
    std::vector<std::vector<long long>> previous(k, std::vector<long long>(2, 0));

    previous[0][0] = 1;

    for (int length = 0; length < n; ++length) {
        for (int i = 0; i < k; ++i) {
            current[i][0] = 0;
            current[i][1] = 0;
        }

        for (int remainder = 0; remainder < k; ++remainder) {
            for (int parity = 0; parity < 2; ++parity) {
                for (int digit = 0; digit < 10; ++digit) {
                    if (length == 0 && digit == 0) continue;
                    if (digit % 2 == parity) continue;

                    int new_remainder = (remainder * 10 + digit) % k;
                    current[new_remainder][1 - parity] = (current[new_remainder][1 - parity] + previous[remainder][parity]) % MOD;
                }
            }
        }
        previous = current;
    }

    long long result = (previous[0][0] + previous[0][1]) % MOD;
    std::cout << result << std::endl;

    return 0;
}