#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n, k, t;
    cin >> n >> k >> t;

    vector<string> message(n);
    for (int i = 0; i < n; i++) {
        cin >> message[i];
    }

    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (message[j].substr(k - t, t) > message[j + 1].substr(k - t, t)) {
                string temp = message[j];
                message[j] = message[j + 1];
                message[j + 1] = temp;
            }
        }
    }

    for (const string& message : message) {
        cout << message << endl;
    }
    return 0;
}