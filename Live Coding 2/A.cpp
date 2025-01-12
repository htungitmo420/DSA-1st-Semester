#include <iostream>
#include <vector>

const int MOD = 1000000007;

long long count_ways(int N, int M) {
    std::vector<std::vector<long long>> dp(N, std::vector<long long>(M, 0));
    dp[0][0] = 1;
    
    for (int sum = 0; sum <= N + M - 2; sum++) {
        for (int i = 0; i <= sum; i++) {
            int j = sum - i;
            if (i >= N || j >= M) continue;
            if (dp[i][j] == 0) continue;

            if (i - 1 >= 0 && j + 2 < M) {
                dp[i - 1][j + 2] = (dp[i - 1][j + 2] + dp[i][j]) % MOD;
            }
            if (i + 1 < N && j + 2 < M) {
                dp[i + 1][j + 2] = (dp[i + 1][j + 2] + dp[i][j]) % MOD;
            }
            if (i + 2 < N && j + 1 < M) {
                dp[i + 2][j + 1] = (dp[i + 2][j + 1] + dp[i][j]) % MOD;
            }
            if (i + 2 < N && j - 1 >= 0) {
                dp[i + 2][j - 1] = (dp[i + 2][j - 1] + dp[i][j]) % MOD;
            }
        }
    }
    return dp[N - 1][M - 1];
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::cout << count_ways(N, M) << "\n";
    return 0;
}