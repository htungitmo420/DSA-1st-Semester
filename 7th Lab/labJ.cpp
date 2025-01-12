#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::string s;
    std::cin >> s;
    
    std::vector<std::pair<std::string, int>> dictionary;
    std::string currentPrefix;
    int dictIndex = 1;
    
    for (char c : s) {
        currentPrefix += c;
        bool found = false;
        for (const auto& entry : dictionary) {
            if (entry.first == currentPrefix) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::string prefixWithoutLastChar = currentPrefix.substr(0, currentPrefix.size() - 1);
            int pos = 0;
            
            if (!prefixWithoutLastChar.empty()) {
                for (const auto& entry : dictionary) {
                    if (entry.first == prefixWithoutLastChar) {
                        pos = entry.second;
                        break;
                    }
                }
            }
            
            std::cout << pos << " " << c << "\n";
            dictionary.push_back({currentPrefix, dictIndex++});
            currentPrefix.clear();
        }
    }
    
    if (!currentPrefix.empty()) {
        int pos = 0;
        for (const auto& entry : dictionary) {
            if (entry.first == currentPrefix) {
                pos = entry.second;
                break;
            }
        }
        if (pos == 0) {
            std::string prefixWithoutLastChar = currentPrefix.substr(0, currentPrefix.size() - 1);
            if (!prefixWithoutLastChar.empty()) {
                for (const auto& entry : dictionary) {
                    if (entry.first == prefixWithoutLastChar) {
                        pos = entry.second;
                        break;
                    }
                }
            }
        }
        std::cout << pos << "\n";
    }
    
    return 0;
}
