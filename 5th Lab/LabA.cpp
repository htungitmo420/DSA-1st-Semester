#include <iostream>

struct Node {
    int key;
    int left;
    int right;
};

int calculateHeight(Node* tree, int node, int* balance, int* heights) {
    if (node == 0) return 0;
    if (heights[node - 1] != -1) return heights[node - 1];
    int leftHeight = calculateHeight(tree, tree[node - 1].left, balance, heights);
    int rightHeight = calculateHeight(tree, tree[node - 1].right, balance, heights);
    balance[node - 1] = rightHeight - leftHeight;
    heights[node - 1] = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    return heights[node - 1];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Node* tree = new Node[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> tree->key >> tree[i].left >> tree[i].right;
    }

    int* balance = new int[n]();
    int* heights = new int[n];

    for (int i = 0; i < n; ++i) {
        heights[i] = -1;
    }
    calculateHeight(tree, 1, balance, heights);

    for (int i = 0; i < n; ++i) {
        std::cout << balance[i] << std::endl;
    }

    return 0;
}
