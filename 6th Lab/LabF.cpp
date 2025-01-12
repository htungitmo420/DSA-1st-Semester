#include <iostream>
#include <vector>

std::vector<int> createPrimeNumbers(int limit) {
    std::vector<bool> isPrime(limit + 1, true);
    std::vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i <= limit && (int)primes.size() < 1000000; i++) {
        if(isPrime[i]) {
            primes.push_back(i);
            if((long long)i * i <= limit) {
                for(int j = i * i; j <= limit; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    return primes;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> primes = createPrimeNumbers(1000000);

    std::vector<int> exponents;
    int remaining = n;
    int primeIndex = 0;

    while(remaining > 0) {
        int k;
        if(remaining >= 3) {
            k = 2;
        } else {
            k = 1;
        }
        int e = (1 << k) - 1;
        exponents.push_back(e);
        remaining -= k;
    }

    std::vector<int> selectedPrimes;
    for(int e : exponents) {
        int currentPrime = primes[primeIndex++];
        for(int j = 0; j < e; j++) {
            selectedPrimes.push_back(currentPrime);
        }
    }

    std::cout << selectedPrimes.size() << "\n";
    for(int i = 0; i < (int)selectedPrimes.size(); i++) {
        std::cout << selectedPrimes[i];
        if(i != (int)selectedPrimes.size() - 1) std::cout << " ";
    }
    std::cout << "\n";

    return 0;
}