#include <iostream>
#include <string>
#include <vector>
#include <queue>

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void HuffmanLength(Node* root, int depth, std::vector<int>& charLength) {
    if (!root) return;
    if (!root->left && !root->right) {
        charLength[root->ch - 'a'] = depth;
        return;
    }
    HuffmanLength(root->left, depth + 1, charLength);
    HuffmanLength(root->right, depth + 1, charLength);
}

int main() {
    std::string s;
    std::cin >> s;

    std::vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            pq.push(new Node('a' + i, freq[i]));
        }
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();

    std::vector<int> charLength(26, 0);
    HuffmanLength(root, 0, charLength);

    long long totalLength = 0;
    for (char c : s) {
        totalLength += charLength[c - 'a'];
    }

    std::cout << totalLength;

    return 0;
}
