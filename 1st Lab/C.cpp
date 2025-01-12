#include <iostream>
#include <string>

bool yesorno(std::string s, int left, int right) {
    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {

    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    int left = 0,right = s.length() -1;

    while (left < right) {
        if (s[left]!=s[right]) {
            if (yesorno(s,left+1,right))
                std::cout << "YES";
            else if (yesorno(s,left,right-1))
                std::cout << "YES";
            else
                std::cout << "NO";
            return 0;    
        }
        left++;
        right--;
    }

    std::cout << "YES" << std::endl;

    return 0;
}