//Code mẫu tham khảo
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int calculateParityBits(int m) {
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

vector<int> insertParityBits(const vector<int>& data, int r) {
    int m = data.size();
    int totalBits = m + r;
    vector<int> encoded(totalBits, 0);

    int j = 0; 
    for (int i = 1; i <= totalBits; i++) {
        if ((i & (i - 1)) == 0) {
            encoded[i - 1] = 0;
        } else {
            encoded[i - 1] = data[j++];
        }
    }
    return encoded;
}

void calculateParityBits(vector<int>& encoded) {
    int totalBits = encoded.size();
    for (int i = 0; (1 << i) <= totalBits; i++) {
        int parityPosition = (1 << i) - 1;
        int parityValue = 0;

        for (int j = parityPosition; j < totalBits; j++) {
            if ((j + 1) & (1 << i)) {
                parityValue ^= encoded[j];
            }
        }
        encoded[parityPosition] = parityValue;
    }
}

int checkAndCorrectError(vector<int>& received) {
    int totalBits = received.size();
    int errorPosition = 0;

    for (int i = 0; (1 << i) <= totalBits; i++) {
        int parityPosition = (1 << i) - 1;
        int parityValue = 0;

        for (int j = parityPosition; j < totalBits; j++) {
            if ((j + 1) & (1 << i)) {
                parityValue ^= received[j];
            }
        }
        if (parityValue != 0) {
            errorPosition += (1 << i);
        }
    }

    if (errorPosition > 0) {
        received[errorPosition - 1] ^= 1;
    }

    return errorPosition;
}

int main() {
    cout << "Nhap so bit du lieu: ";
    int m;
    cin >> m;

    vector<int> data(m);
    cout << "Nhap cac bit da lieu (0 hoac 1): ";
    for (int i = 0; i < m; i++) {
        cin >> data[i];
    }

    int r = calculateParityBits(m);

    vector<int> encoded = insertParityBits(data, r);
    calculateParityBits(encoded);

    cout << "Chuoi du lieu sau khi ma hoa Hamming: ";
    for (int bit : encoded) {
        cout << bit;
    }
    cout << endl;

    cout << "\nNhap chuoi dy lieu nhan đưoc (có thể chứa lỗi): ";
    vector<int> received(encoded.size());
    for (int i = 0; i < received.size(); i++) {
        cin >> received[i];
    }

    int errorPosition = checkAndCorrectError(received);

    if (errorPosition == 0) {
        cout << "\nKhong co loi trong chuoi du lieu." << endl;
    } else {
        cout << "\nLoi phat hien tai vi tri: " << errorPosition << endl;
        cout << "Chuoi du lieu sau khi sua loi: ";
        for (int bit : received) {
            cout << bit;
        }
        cout << endl;
    }

    return 0;
}