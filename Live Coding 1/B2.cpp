#include <iostream>
#include <ctime>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void merge(int arr[], int left, int mid, int right) {
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    int* leftArray = new int[sizeLeft];
    int* rightArray = new int[sizeRight];

    for (int i = 0; i < sizeLeft; ++i) leftArray[i] = arr[left + i];
    for (int i = 0; i < sizeRight; ++i) rightArray[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < sizeLeft && j < sizeRight) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < sizeLeft) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < sizeRight) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }

}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

    mergeSort(all_points, 0, all_number_size - 1);

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
    for (int i = 1; i < unique_size; ++i) {
        segment_count[i] = segment_count[i - 1] + diff[i];
    }

    for (int i = 0; i < q; ++i) {
        int pos_index = binarySearch(all_points, unique_size, number[i]);
        std::cout << segment_count[pos_index] << std::endl;
    }


    return 0;
}