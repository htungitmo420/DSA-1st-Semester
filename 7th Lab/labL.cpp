#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int findErrorPosition(const std::string &code) {
    int n = code.size();
    int errorPosition = 0;

    for (int i = 0; i < std::log2(n) + 1; ++i) {
        int parity = 0;
        for (int j = 1; j <= n; ++j) {
            if (j & (1 << i)) {
                parity ^= (code[j - 1] - '0');
            }
        }
        if (parity) {
            errorPosition += (1 << i);
        }
    }

    return errorPosition;
}

std::string correctHammingCode(std::string code) {
    int errorPosition = findErrorPosition(code);

    if (errorPosition > 0 && errorPosition <= code.size()) {
        code[errorPosition - 1] = (code[errorPosition - 1] == '0') ? '1' : '0';
    }

    std::string decoded;
    int power = 1;
    for (int i = 0; i < code.size(); ++i) {
        if (i + 1 == power) {
            power *= 2;
        } else {
            decoded += code[i];
        }
    }

    return decoded;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int t;
    std::cin >> t;
    std::vector<std::string> encodedMessages(t);

    for (int i = 0; i < t; ++i) {
        std::cin >> encodedMessages[i];
    }

    for (const auto &encoded : encodedMessages) {
        std::cout << correctHammingCode(encoded) << "\n";
    }

    return 0;
}