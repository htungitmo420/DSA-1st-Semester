#include <iostream>
#include <vector>

std::vector<long long> calculateRowProfits(const std::vector<long long>& row) {
    int k = row.size();
    std::vector<long long> leftSums(k + 1, 0);
    std::vector<long long> rightSums(k + 1, 0);

    for (int i = 1; i <= k; ++i) {
        leftSums[i] = leftSums[i - 1] + row[i - 1];
    }

    for (int i = 1; i <= k; ++i) {
        rightSums[i] = rightSums[i - 1] + row[k - i];
    }

    std::vector<long long> maxProfits(k + 1, 0);
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k - i; ++j) {
            maxProfits[i + j] = std::max(maxProfits[i + j], leftSums[i] + rightSums[j]);
        }
    }

    return maxProfits;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<long long>> rowProfits(n);

    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        std::vector<long long> row(k);
        
        for (int j = 0; j < k; ++j) {
            std::cin >> row[j];
        }
        
        rowProfits[i] = calculateRowProfits(row);
    }

    std::vector<long long> dp(m + 1, 0);

for (int i = 0; i < rowProfits.size(); ++i) {
    const std::vector<long long>& profits = rowProfits[i];
    for (int j = m; j >= 0; --j) {
        for (int k = 0; k < profits.size() && k <= j; ++k) {
            long long newProfit = dp[j - k] + profits[k];
            if (newProfit > dp[j]) {
                dp[j] = newProfit;
            }
        }
    }
}

    std::cout << dp[m];

    return 0;
}