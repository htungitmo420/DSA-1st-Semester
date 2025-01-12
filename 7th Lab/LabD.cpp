#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> field(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> field[i][j];
        }
    }

    std::vector<std::vector<long long>> dpMasha(n, std::vector<long long>(m, 0));
    dpMasha[0][0] = field[0][0];
    for (int i = 1; i < n; ++i) {
        dpMasha[i][0] = dpMasha[i-1][0] + field[i][0];
    }
    for (int j = 1; j < m; ++j) {
        dpMasha[0][j] = dpMasha[0][j-1] + field[0][j];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dpMasha[i][j] = std::max(dpMasha[i-1][j], dpMasha[i][j-1]) + field[i][j];
        }
    }

    std::vector<std::vector<long long>> dpDasha(n, std::vector<long long>(m, 0));
    dpDasha[n-1][m-1] = field[n-1][m-1];
    for (int i = n-2; i >= 0; --i) {
        dpDasha[i][m-1] = dpDasha[i+1][m-1] + field[i][m-1];
    }
    for (int j = m-2; j >= 0; --j) {
        dpDasha[n-1][j] = dpDasha[n-1][j+1] + field[n-1][j];
    }
    for (int i = n-2; i >= 0; --i) {
        for (int j = m-2; j >= 0; --j) {
            dpDasha[i][j] = std::max(dpDasha[i+1][j], dpDasha[i][j+1]) + field[i][j];
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        std::cout << dpMasha[x][y] + dpDasha[x][y] - field[x][y] << "\n";
    }
    return 0;
}