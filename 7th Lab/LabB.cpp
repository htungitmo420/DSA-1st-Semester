#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::string s;
    std::cin >> s;

    int count[26] = {0};
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            count[c - 'a']++;
        }
    }

    double low_freq[26] = {0.0}, high_freq[26] = {0.0};
    double total = s.size(), current = 0.0;

    for (int i = 0; i < 26; ++i) {
        if (count[i] > 0) {
            low_freq[i] = current;
            high_freq[i] = current + (count[i] / total);
            current = high_freq[i];
        }
    }

    double current_low = 0.0;
    double current_high = 1.0;

    for (char c : s) {
        if (c < 'a' || c > 'z') continue;
        int index = c - 'a';
        double range = current_high - current_low;
        current_high = current_low + range * high_freq[index];
        current_low = current_low + range * low_freq[index];
    }

    std::cout << std::fixed << std::setprecision(6) << current_low << "\n";
    return 0;
}