#include <iostream>
#include <vector>

char getchar(const std::string& str, int index) {
    if (index >= 0 && index < str.length()) {
        return str[index];
    }
    return '\0';
}

void radixSort(std::vector<std::string>& mes, int pos) {
    const int ascii_chars = 256;
    std::vector<int> count(ascii_chars, 0);

    for (const std::string& message : mes) { 
        char ch = getchar(message, pos);
        count[ch]++;
    }

    std::vector<int> startIndex(ascii_chars, 0); 
    int sum = 0;
    for (int i = 0; i < ascii_chars; i++) {
        startIndex[i] = sum;
        sum += count[i];
    }

    std::vector<std::string> sortedmes(mes.size()); 

    for (const std::string& message : mes) {  
        char ch = getchar(message, pos);
        int index = startIndex[ch];
        sortedmes[index] = message;
        startIndex[ch]++;
    }

    mes = sortedmes;
}

int main() {
    int n, k, t;
    std::cin >> n >> k >> t;
    std::vector<std::string> mes(n);

    for (int i = 0; i < n; i++) {
        std::cin >> mes[i];
    }
    for (int i = k - 1; i >= k - t; i--) {
        radixSort(mes, i);
    }
    for (const std::string& message : mes) {
        std::cout << message << "\n";
    }
    return 0;
}