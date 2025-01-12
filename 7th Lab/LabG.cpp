#include <iostream>
#include <vector>
#include <string>

std::vector<std::pair<char, int>> decodeRLE(const std::string &rle) {
    std::vector<std::pair<char, int>> decoded;
    int i = 0;
    while (i < rle.size()) {
        char ch = rle[i++];
        int num = 0;
        while (i < rle.size() && isdigit(rle[i])) {
            num = num * 10 + (rle[i++] - '0');
        }
        decoded.push_back({ch, num});
    }
    return decoded;
}

long long calculateDifferences(std::vector<std::pair<char, int>> &code1, std::vector<std::pair<char, int>> &code2) {
    long long differences = 0;
    int i = 0, j = 0;
    while (i < code1.size() && j < code2.size()) {
        if (code1[i].first == code2[j].first) {
            int minCount = std::min(code1[i].second, code2[j].second);
            code1[i].second -= minCount;
            code2[j].second -= minCount;
            if (code1[i].second == 0) i++;
            if (code2[j].second == 0) j++;
        } else {
            differences += std::min(code1[i].second, code2[j].second);
            if (code1[i].second < code2[j].second) {
                code2[j].second -= code1[i].second;
                i++;
            } else {
                code1[i].second -= code2[j].second;
                j++;
            }
        }
    }
    while (i < code1.size()) differences += code1[i++].second;
    while (j < code2.size()) differences += code2[j++].second;
    return differences;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m;
    long long k;
    std::cin >> n >> m >> k;
    std::string rle1, rle2;
    std::cin >> rle1 >> rle2;

    auto code1 = decodeRLE(rle1);
    auto code2 = decodeRLE(rle2);

    long long differences = calculateDifferences(code1, code2);

    if (differences < k) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}