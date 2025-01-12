#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int key) {
        data = key;
        left = right = nullptr;
    }
};

Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int MaxHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = MaxHeight(root->left);
    int rightHeight = MaxHeight(root->right);
    int maxHeight;

    if (leftHeight > rightHeight) {
        maxHeight = leftHeight;
    } else {
        maxHeight = rightHeight;
    }

    return 1 + maxHeight;
}

int MinHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr) {
        return 1 + MinHeight(root->right);
    } if (root->right == nullptr) {
        return 1 + MinHeight(root->left);
    }
    int leftHeight = MinHeight(root->left);
    int rightHeight = MinHeight(root->right);
    int minHeight;

    if (leftHeight < rightHeight) {
        minHeight = leftHeight;
    } else {
        minHeight = rightHeight;
    }
    return 1 + minHeight;
}

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    
    int value;
    std::cin >> value;
    Node* root = new Node(value);

    for (int i = 1; i < n; i++) {
        std::cin >> value;
        root = insertNode(root, value);
    }

    int maxHeight = MaxHeight(root);
    int minHeight = MinHeight(root);

    std::cout << (maxHeight - minHeight) << std::endl;

    return 0;
}