// Thật ra bài này không được dùng priority queue =))))
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

struct Compare {
    bool operator()(const std::tuple<double, int, int>& a, const std::tuple<double, int, int>& b) {
        return std::get<0>(a) > std::get<0>(b);
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> primes(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> primes[i];
    }

    std::priority_queue<std::tuple<double, int, int>, std::vector<std::tuple<double, int, int>>, Compare> pq;

    for (int j = 1; j < n; ++j) {
        pq.push(std::make_tuple((double)primes[0] / primes[j], 0, j));
    }

    std::tuple<double, int, int> fraction;
    for (int count = 1; count < k; ++count) {
        fraction = pq.top();
        pq.pop();
        
        int i = std::get<1>(fraction);  
        int j = std::get<2>(fraction);  

        if (i + 1 < j) {
            pq.push(std::make_tuple((double)primes[i + 1] / primes[j], i + 1, j));
        }
    }

    fraction = pq.top();
    int i = std::get<1>(fraction);
    int j = std::get<2>(fraction);
    std::cout << primes[i] << " " << primes[j] << "\n";

    return 0;
}