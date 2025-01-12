#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
    Node (int key) {
        data = key;
        left = right = nullptr;
    }
};

Node* insertNode(Node* root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insertNode(root->left,data);
    } else {
        root->right = insertNode(root->right,data);
    }
    return root;
}

Node* successor(Node* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root, int x) {
    if (root == nullptr) return root;
    if (x < root->data) {
        root->left = deleteNode(root->left, x);
    } else if (x > root->data) {
        root->right = deleteNode(root->right, x);
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
        Node* succ = successor(root);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}

bool NodeExist(Node* root, int target) {
    if (root == nullptr) return false;
    if (root->data == target) return true;
    if (target < root->data) return NodeExist(root->left, target);
    return NodeExist(root->right, target);
}

Node* Min(Node* root, int x) {
    Node* min = nullptr;
    while (root) {
        if (root->data > x) {
            min = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return min;
}

Node* Max(Node* root, int x) {
    Node* max = nullptr;
    while (root) {
        if (root->data < x) {
            max = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Node* root = nullptr;
    int op, x;

    while (std::cin >> op >> x) {
        switch(op) {
            case 0:
                root = insertNode(root, x);
                break;
            case 1:
                root = deleteNode(root, x);
                break;
            case 2:
                std::cout << (NodeExist(root, x) ? "true" : "false") << '\n';
                break;
            case 3: {
                Node* result = Min(root, x);
                if (result) {
                    std::cout << result->data << '\n';
                } else {
                    std::cout << "none" << '\n';
                }
                break;
            }
            case 4: {
                Node* result = Max(root, x);
                if (result) {
                    std::cout << result->data << '\n';
                } else {
                    std::cout << "none" << '\n';
                }
                break;
            }
        }
    }
    return 0;
}
