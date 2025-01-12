#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> houses(n);
    
    for (int i = 0; i < n; ++i) {
        int age;
        std::cin >> age;
        houses[i] = {age, i + 1};
    }
    
    std::sort(houses.begin(), houses.end());
    
    std::vector<int> dp(n, INT_MAX);
    dp[0] = houses[0].second - 1 + 1;

    for (int i = 1; i < n; ++i) {
        int travel_time = std::abs(houses[i].second - houses[i - 1].second);
        dp[i] = dp[i - 1] + travel_time + 1; 
    }
    
    std::cout << dp[n - 1] << std::endl;
    
    return 0;
}