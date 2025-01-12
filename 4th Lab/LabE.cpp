#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int key) {
        data = key;
        right = left = nullptr;
    }
};

int findIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

Node* BST(const std::vector<int>& inOrder, const std::vector<int>& preOrder, int inStart, int inEnd, int& preIndex) {
    if (inStart > inEnd) {
        return nullptr;
    }

    Node* node = new Node(preOrder[preIndex++]);

    if (inStart == inEnd) {
        return node;
    }

    int inIndex = -1;
    for (int i = inStart; i <= inEnd; i++) {
        if (inOrder[i] == node->data) {
            inIndex = i;
            break;
        }
    }
    
    if (inIndex == -1) {
        return nullptr;
    }

    node->left = BST(inOrder, preOrder, inStart, inIndex - 1, preIndex);
    node->right = BST(inOrder, preOrder, inIndex + 1, inEnd, preIndex);

    return node;
}

bool validatePostOrder(Node* node, const std::vector<int>& postOrder, int& index) {
    if (!node) {
        return true;
    }

    if (!validatePostOrder(node->left, postOrder, index)) {
        return false;
    }
    if (!validatePostOrder(node->right, postOrder, index)) {
        return false;
    }

    return (node->data == postOrder[index++]);
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> preorder(n), inorder(n), postorder(n);

    for (int i = 0; i < n; i++) {
        std::cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> inorder[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> postorder[i];
    }

    int preIndex = 0;
    Node* root = BST(inorder, preorder, 0, n-1, preIndex);
    
    if (!root) {
        std::cout << "NO";
        return 0;
    }

    int postIndex = 0;
    bool isValid = validatePostOrder(root, postorder, postIndex) && (postIndex == n);
    
    std::cout << (isValid ? "YES" : "NO");

    return 0;
}