#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Comparison function for priority queue (min-heap)
struct Compare {
    bool operator()(const tuple<double, int, int>& a, const tuple<double, int, int>& b) {
        return get<0>(a) > get<0>(b);
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> primes(n);
    for (int i = 0; i < n; ++i) {
        cin >> primes[i];
    }

    // Min-heap (priority queue)
    priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, Compare> pq;

    // Initialize the heap with fractions with numerator arr[0] and denominators arr[1], ..., arr[n-1]
    for (int j = 1; j < n; ++j) {
        pq.push(make_tuple((double)primes[0] / primes[j], 0, j));
    }

    // Pop k-1 smallest fractions from the heap
    tuple<double, int, int> fraction;
    for (int count = 1; count < k; ++count) {
        fraction = pq.top();
        pq.pop();
        
        int i = get<1>(fraction);  // Current numerator index
        int j = get<2>(fraction);  // Current denominator index

        // Push the next fraction with a larger numerator but the same denominator
        if (i + 1 < j) {
            pq.push(make_tuple((double)primes[i + 1] / primes[j], i + 1, j));
        }
    }

    // The k-th smallest fraction will now be at the top of the heap
    fraction = pq.top();
    int i = get<1>(fraction);
    int j = get<2>(fraction);
    cout << primes[i] << " " << primes[j] << endl;

    return 0;
}