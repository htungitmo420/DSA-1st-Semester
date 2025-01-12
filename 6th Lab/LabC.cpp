#include <iostream>
#include <vector>

struct Worker {
    int salary;
    int index;
};

struct BusyWorker {
    long long freeTime;
    int salary;
    int index;
};

struct Order {
    long long time;
    int duration;
};

void pushFreeWorker(std::vector<Worker>& heap, const Worker& value) {
    heap.push_back(value);
    int i = heap.size() - 1;
    while (i > 0 && heap[i].salary < heap[(i - 1) / 2].salary) {
        Worker temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Worker popFreeWorker(std::vector<Worker>& heap) {
    Worker root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    int n = heap.size();
    int i = 0;
    while (true) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && heap[left].salary < heap[smallest].salary) {
            smallest = left;
        }
        if (right < n && heap[right].salary < heap[smallest].salary) {
            smallest = right;
        }
        if (smallest != i) {
            Worker temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

void pushBusyWorker(std::vector<BusyWorker>& heap, const BusyWorker& value) {
    heap.push_back(value);
    int i = heap.size() - 1;
    while (i > 0 && heap[i].freeTime < heap[(i - 1) / 2].freeTime) {
        BusyWorker temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

BusyWorker popBusyWorker(std::vector<BusyWorker>& heap) {
    BusyWorker root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    int n = heap.size();
    int i = 0;
    while (true) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && heap[left].freeTime < heap[smallest].freeTime) {
            smallest = left;
        }
        if (right < n && heap[right].freeTime < heap[smallest].freeTime) {
            smallest = right;
        }
        if (smallest != i) {
            BusyWorker temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Worker> workers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> workers[i].salary;
        workers[i].index = i;
    }

    std::vector<Worker> availableWorkers;
    for (int i = 0; i < n; ++i) {
        pushFreeWorker(availableWorkers, workers[i]);
    }

    std::vector<BusyWorker> busyWorkers;

    long long totalSalary = 0;

    std::vector<Order> orders(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> orders[i].time >> orders[i].duration;
    }

    for (int i = 0; i < m; ++i) {
        long long currentTime = orders[i].time;
        int duration = orders[i].duration;

        while (!busyWorkers.empty() && busyWorkers[0].freeTime <= currentTime) {
            Worker freedWorker;
            freedWorker.salary = busyWorkers[0].salary;
            freedWorker.index = busyWorkers[0].index;
            popBusyWorker(busyWorkers);
            pushFreeWorker(availableWorkers, freedWorker);
        }

        if (!availableWorkers.empty()) {
            Worker assignedWorker = popFreeWorker(availableWorkers);
            long long freeTime = currentTime + duration;

            BusyWorker busyWorker;
            busyWorker.freeTime = freeTime;
            busyWorker.salary = assignedWorker.salary;
            busyWorker.index = assignedWorker.index;
            pushBusyWorker(busyWorkers, busyWorker);

            totalSalary += (long long)duration * assignedWorker.salary;
        }
    }
    std::cout << totalSalary << std::endl;
    return 0;
}