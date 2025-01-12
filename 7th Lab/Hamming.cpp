#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Hàm tính số lượng bit kiểm tra cần thiết
int calculateParityBits(int m) {
    int r = 0;
    while (pow(2, r) < m + r + 1) {
        r++;
    }
    return r;
}

// Hàm chèn các bit kiểm tra vào dữ liệu ban đầu
vector<int> insertParityBits(const vector<int>& data, int r) {
    int m = data.size();
    int totalBits = m + r;
    vector<int> encoded(totalBits, 0);

    int j = 0; // Index for data bits
    for (int i = 1; i <= totalBits; i++) {
        if ((i & (i - 1)) == 0) {
            // Vị trí là lũy thừa của 2 -> bit kiểm tra
            encoded[i - 1] = 0;
        } else {
            // Vị trí khác -> gán dữ liệu gốc
            encoded[i - 1] = data[j++];
        }
    }
    return encoded;
}

// Hàm tính giá trị các bit kiểm tra
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

// Hàm kiểm tra và sửa lỗi
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
        // Sửa lỗi bằng cách đảo bit tại vị trí lỗi
        received[errorPosition - 1] ^= 1;
    }

    return errorPosition;
}

int main() {
    // Nhập dữ liệu gốc
    cout << "Nhap so bit du lieu: ";
    int m;
    cin >> m;

    vector<int> data(m);
    cout << "Nhap cac bit da lieu (0 hoac 1): ";
    for (int i = 0; i < m; i++) {
        cin >> data[i];
    }

    // Tính số lượng bit kiểm tra
    int r = calculateParityBits(m);

    // Chèn và tính giá trị các bit kiểm tra
    vector<int> encoded = insertParityBits(data, r);
    calculateParityBits(encoded);

    cout << "Chuoi du lieu sau khi ma hoa Hamming: ";
    for (int bit : encoded) {
        cout << bit;
    }
    cout << endl;

    // Nhập chuỗi dữ liệu nhận được
    cout << "\nNhap chuoi dy lieu nhan đưoc (có thể chứa lỗi): ";
    vector<int> received(encoded.size());
    for (int i = 0; i < received.size(); i++) {
        cin >> received[i];
    }

    // Kiểm tra và sửa lỗi
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