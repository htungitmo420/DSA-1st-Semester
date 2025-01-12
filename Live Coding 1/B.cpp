#include <iostream>
#include <ctime>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int randomPivot(int left, int right) {
    return left + rand() % (right - left + 1);
}

int hoarePartition(int arr[], int left, int right) {
    int pivotIndex = randomPivot(left, right);
    int pivot = arr[pivotIndex];
    int i = left - 1;
    int j = right + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            return j;
        }
    }
}

void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int hoare = hoarePartition(arr, left, right);
        quickSort(arr, left, hoare);
        quickSort(arr, hoare + 1, right);
    }
}

int binarySearch(int arr[], int size, int value) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, q;
    std::cin >> n;

    int* begin = new int[n];
    int* end = new int[n];

    for (int i = 0; i < n; ++i) std::cin >> begin[i] >> end[i];

    std::cin >> q;
    int* number = new int[q];
    for (int i = 0; i < q; ++i) std::cin >> number[i];

    int all_number_size = 2 * n + q;
    int* all_points = new int[all_number_size];
    int index = 0;

    for (int i = 0; i < n; ++i) {
        all_points[index++] = begin[i];
        all_points[index++] = end[i] + 1;
    }

    for (int i = 0; i < q; ++i) all_points[index++] = number[i];

    srand(time(NULL));
    quickSort(all_points, 0, all_number_size - 1);

    int unique_size = 1;
    for (int i = 1; i < all_number_size; ++i) {
        if (all_points[i] != all_points[i - 1]) {
            all_points[unique_size++] = all_points[i];
        }
    }

    int* diff = new int[unique_size + 1]();

    for (int i = 0; i < n; ++i) {
        int left = binarySearch(all_points, unique_size, begin[i]);
        int right = binarySearch(all_points, unique_size, end[i] + 1);
        diff[left]++;
        diff[right]--;
    }

    int* segment_count = new int[unique_size]();
    segment_count[0] = diff[0];
    for (int i = 1; i < unique_size; ++i) segment_count[i] = segment_count[i - 1] + diff[i];

    for (int i = 0; i < q; ++i) {
        int pos_index = binarySearch(all_points, unique_size, number[i]);
        std::cout << segment_count[pos_index] << std::endl;
    }
    return 0;
}
