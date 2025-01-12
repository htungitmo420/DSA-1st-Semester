#include <iostream>
#include <vector>
using namespace std;

void quicksort_lomuto(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = arr[left];
        int l = left + 1;
        int r = right;

        while (l <= r) {
            if (arr[l] > pivot && arr[r] < pivot) {
                swap(arr[l], arr[r]);
            }
            if (arr[l] <= pivot) {
                l++;
            }
            if (arr[r] >= pivot) {
                r--;
            }
        }

        swap(arr[left], arr[r]);

        quicksort_lomuto(arr, left, r - 1);
        quicksort_lomuto(arr, r + 1, right);
    }
}

bool boyars_seats(int distance, int k, const vector<int>& seats, int n) {
    int count = 1;
    int lastSeat = seats[0];
    for (int i = 1; i < n; ++i) {
        if (seats[i] - lastSeat >= distance) {
            count++;
            lastSeat = seats[i];
        }
    }
    return count >= k;
}

int binarysearch(int left, int right, int K, const vector<int>& seats, int N) {
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (boyars_seats(mid, K, seats, N)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> seats(n);
    for (int i = 0; i < n; ++i) {
        cin >> seats[i];
    }

    quicksort_lomuto(seats, 0, n - 1);

    int left = 1;
    int right = seats[n - 1] - seats[0];
    int result = binarysearch(left, right, k, seats, n);

    cout << result << endl;

    return 0;
}