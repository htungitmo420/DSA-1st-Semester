#include <iostream>

struct Node{
    long long data;
    Node* right;
    Node* left;
    long long count;

    Node(long long weight) {
        data = weight;
        left = right = nullptr;
        count = 1;
    }
};

Node* insertNode(Node* root, long long data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    root->count++;
    return root;
}

Node* deleteNode(Node* root, long long target) {
    if (root == nullptr) return root;
    if (target < root->data) {
        root->left = deleteNode(root->left, target);
    } else if (target > root->data) {
        root->right = deleteNode(root->right, target);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* succ = root->right;
        while (succ && succ->left) succ = succ->left;
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    root->count--;
    return root;
}

long long findKLargest(Node* root, int k) {
    Node* current = root;
    long long count = 0;
    long long result = -1;

    while (current != nullptr) {
        int rightCount = (current->right != nullptr) ? current->right->count : 0;

        if (count + rightCount + 1 == k) {
            result = current->data;
            break;
        }

        if (count + rightCount + 1 < k) {
            count += rightCount + 1;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Node* root = nullptr;

    for (int i = 0; i < n; i++) {
        int op, k;
        std::cin >> op >> k;

        if (op == 1) root = insertNode(root, k);
        if (op == 0) {
            long long result = findKLargest(root, k);
            std::cout << result << std::endl;
        }
        if (op == -1) root = deleteNode(root,k);
    }

    return 0;
}