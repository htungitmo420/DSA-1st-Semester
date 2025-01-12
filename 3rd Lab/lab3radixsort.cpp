#include <iostream>
#include <vector>
using namespace std;

char getchar(const string& str, int index) {
    if (index >= 0 && index < str.length()) {
        return str[index];
    }
    return '\0'; //null
}

void radixSort(vector<string>& mes, int pos) {
    const int ascii_chars = 256;
    vector<int> count(ascii_chars, 0);

    for (const string& message : mes) { 
        char ch = getchar(message, pos);
        count[ch]++;
    }

    vector<int> startIndex(ascii_chars, 0); 
    int sum = 0;
    for (int i = 0; i < ascii_chars; i++) {
        startIndex[i] = sum;
        sum += count[i];
    }

    vector<string> sortedmes(mes.size()); 

    for (const string& message : mes) {  
        char ch = getchar(message, pos);
        int index = startIndex[ch];
        sortedmes[index] = message;
        startIndex[ch]++;
    }

    mes = sortedmes;
}

int main() {
    int n, k, t;
    cin >> n >> k >> t;
    vector<string> mes(n);

    for (int i = 0; i < n; i++) {
        cin >> mes[i];
    }
    for (int i = k - 1; i >= k - t; i--) {
        radixSort(mes, i);
    }
    for (const string& message : mes) {
        cout << message << endl;
    }
    return 0;
}