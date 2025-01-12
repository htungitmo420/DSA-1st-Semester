#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
    Node(int key) {
        data = key;
        left = right = nullptr;
    }
};

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void Inorder(Node* node) {
    if(node == nullptr) {
        return;
    }

    Inorder(node->left);
    std::cout << node->data << " ";
    Inorder(node->right);
}

int main() {
    int n;
    std::cin >> n;

    Node* root = nullptr;
    for (int i = 0; i < n; i++){
        int data;
        std::cin >> data;
        root = insert(root, data);
    }

    Inorder(root);
    std::cout << std::endl;

    return 0;
}