#include <iostream>
#include <vector>
#include <string>

struct PriorityQueue {
    std::vector<int> heap;

    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent] <= heap[i]) break;

            std::swap(heap[i], heap[parent]);
            i = parent;
        }
    }

    void siftDown(int i) {
        int n = heap.size();
        while (true) {
            int minIndex = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && heap[left] < heap[minIndex]) {
                minIndex = left;
            }
            if (right < n && heap[right] < heap[minIndex]) {
                minIndex = right;
            }
            if (minIndex == i) break;

            std::swap(heap[i], heap[minIndex]);
            i = minIndex;
        }
    }

    void insert(int x) {
        heap.push_back(x);
        siftUp(heap.size() - 1);
    }

    std::string extractMin() {
        if (heap.empty()) {
            return "*";
        } else {
            int minElement = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) {
                siftDown(0);
            }
            return std::to_string(minElement);
        }
    }

    void merge(PriorityQueue& other) {
        for (int val : other.heap) {
            heap.push_back(val);
        }
        for (int i = heap.size() / 2; i >= 0; --i) {
            siftDown(i);
        }
    }

    void decreaseKey(int x, int y) {
        if (y >= x) return;
        for (int i = 0; i < heap.size(); ++i) {
            if (heap[i] == x) {
                heap[i] = y;
                siftUp(i);
                break;
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string cmd;
    std::vector<PriorityQueue*> queues;

    while (std::cin >> cmd) {
        if (cmd == "create") {
            queues.push_back(new PriorityQueue());
        } else if (cmd == "insert") {
            int k, x;
            std::cin >> k >> x;
            queues[k]->insert(x);
        } else if (cmd == "extract-min") {
            int k;
            std::cin >> k;
            std::cout << queues[k]->extractMin() << "\n";
        } else if (cmd == "merge") {
            int k, m;
            std::cin >> k >> m;
            PriorityQueue* newQueue = new PriorityQueue();
            newQueue->merge(*queues[k]);
            newQueue->merge(*queues[m]);
            queues.push_back(newQueue);
        } else if (cmd == "decrease-key") {
            int k, x, y;
            std::cin >> k >> x >> y;
            queues[k]->decreaseKey(x, y);
        }
    }
    return 0;
}
