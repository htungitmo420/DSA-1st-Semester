#include <iostream>

const int MAX_N = 1000000;

int maxHeap[MAX_N];
int maxHeapSize = 0;

int minHeap[MAX_N];
int minHeapSize = 0;

void siftUpMax(int index) {
    while (index > 0 && maxHeap[index] > maxHeap[(index - 1) / 2]) {
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[(index - 1) / 2];
        maxHeap[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

void siftDownMax(int index) {
    int largest = index;
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < maxHeapSize && maxHeap[left] > maxHeap[largest]) {
            largest = left;
        }
        if (right < maxHeapSize && maxHeap[right] > maxHeap[largest]) {
            largest = right;
        }
        if (largest != index) {
            int temp = maxHeap[index];
            maxHeap[index] = maxHeap[largest];
            maxHeap[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}

void pushMaxHeap(int x) {
    maxHeap[maxHeapSize] = x;
    siftUpMax(maxHeapSize);
    maxHeapSize++;
}

int popMaxHeap() {
    int result = maxHeap[0];
    maxHeapSize--;
    maxHeap[0] = maxHeap[maxHeapSize];
    siftDownMax(0);
    return result;
}


void siftUpMin(int index) {
    while (index > 0 && minHeap[index] < minHeap[(index - 1) / 2]) {
        int temp = minHeap[index];
        minHeap[index] = minHeap[(index - 1) / 2];
        minHeap[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

void siftDownMin(int index) {
    int smallest = index;
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < minHeapSize && minHeap[left] < minHeap[smallest]) {
            smallest = left;
        }
        if (right < minHeapSize && minHeap[right] < minHeap[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            int temp = minHeap[index];
            minHeap[index] = minHeap[smallest];
            minHeap[smallest] = temp;
            index = smallest;
        } else {
            break;
        }
    }
}

void pushMinHeap(int x) {
    minHeap[minHeapSize] = x;
    siftUpMin(minHeapSize);
    minHeapSize++;
}

int popMinHeap() {
    int result = minHeap[0];
    minHeapSize--;
    minHeap[0] = minHeap[minHeapSize];
    siftDownMin(0);
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    int totalElements = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        totalElements++;

        if (maxHeapSize == 0 || x <= maxHeap[0]) {
            pushMaxHeap(x);
        } else {
            pushMinHeap(x);
        }

        if (maxHeapSize > minHeapSize + 1) {
            int movedValue = popMaxHeap();
            pushMinHeap(movedValue);
        } else if (minHeapSize > maxHeapSize) {
            int movedValue = popMinHeap();
            pushMaxHeap(movedValue);
        }

        int median;
        if (totalElements % 2 == 1) {
            median = maxHeap[0];
        } else {
            median = (maxHeap[0] + minHeap[0]) / 2;
        }

        std::cout << median << "\n";
    }

    return 0;
}