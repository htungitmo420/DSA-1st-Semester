#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;

    std::string row;
    std::vector<int> currentRow(m, 0); 
    int maxSize = 0, bestRow = 0, bestCol = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> row;
        int prev = 0; 
        for (int j = 0; j < m; ++j) {
            int temp = currentRow[j]; 

            if (row[j] == '5') {
                if (i == 0 || j == 0) {
                    currentRow[j] = 1; 
                } else {
                    currentRow[j] = std::min(prev, std::min(currentRow[j], currentRow[j - 1])) + 1;
                }
                if (currentRow[j] > maxSize) {
                    maxSize = currentRow[j];
                    bestRow = i;
                    bestCol = j;
                } else if (currentRow[j] == maxSize) {
                    if (i > bestRow || (i == bestRow && j > bestCol)) {
                        bestRow = i;
                        bestCol = j;
                    }
                }
            } else {
                currentRow[j] = 0; 
            }
            prev = temp; 
        }
    }

    int topLeftRow = bestRow - maxSize + 1;
    int topLeftCol = bestCol - maxSize + 1;

    std::cout << maxSize << " " << topLeftRow + 1 << " " << topLeftCol + 1 << "\n";
    return 0;
}
