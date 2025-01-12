#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int key) {
        data = key;
        left = right = nullptr;
    }
};

void insertNode(Node* node, int data) {
    if (data == node->data) return;
    if (data < node->data) {
        if (node->left) {
            insertNode(node->left, data);
        } else {
            node->left = new Node(data);
        }
    } else {
        if (node->right) {
            insertNode(node->right, data);
        } else {
            node->right = new Node(data);
        }
    }
}

std::vector<int> rightMostValueBST(Node* node) {
    std::vector<int> result;
    if (!node) return result;
    
    std::queue<Node*> q;
    q.push(node);
    
    while (!q.empty()) {
        int levelSize = q.size();
        int rightMostValue = 0;

        for (int i = 0; i < levelSize; i++) {
            Node* curr = q.front();
            q.pop();

            rightMostValue = curr->data;

            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        result.push_back(rightMostValue);
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;
    
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int value;
        std::cin >> value;
        if (!root) {
            root = new Node(value);
        } else {
            insertNode(root, value);
        }
    }
    
    std::vector<int> result = rightMostValueBST(root);
    for (int value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}