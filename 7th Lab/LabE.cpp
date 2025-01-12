#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& lis, int value) {
    int left = 0, right = lis.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (lis[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> lis;
    for (int i = 0; i < n; ++i) {
        int pos = binarySearch(lis, a[i]);
        if (pos == lis.size()) {
            lis.push_back(a[i]);
        } else {
            lis[pos] = a[i];
        }
    }

    std::cout << lis.size();
    return 0;
}