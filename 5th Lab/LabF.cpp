#include <iostream>

struct Node {
    long long data;
    Node* right; 
    Node* left;
    int height;
    Node (long long key) {
        data = key;
        right = left = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->right) - getHeight(node->left);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insertNode(Node* node, long long data, bool& duplicate) {
    if (!node) {
        duplicate = false;
        return new Node(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data, duplicate);
    }
    else if (data > node->data) {
        node->right = insertNode(node->right, data, duplicate);
    }
    else {
        duplicate = true;
        return node;
    }

    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    //RR
    if (balance > 1 && data > node->right->data) 
        return rotateLeft(node);
    //RL
    if (balance > 1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    //LL
    if (balance < -1 && data < node->left->data)
        return rotateRight(node);
    //LR
    if (balance < -1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

Node* maxValueNode(Node* node) {
    Node* current = node;
    while (current->right != nullptr)
        current = current->right;
    return current;
}

Node* deleteNode(Node* root, long long data, bool& deleted) {
    if (!root) {
        deleted = false;
        return root;
    }
    if (data < root->data)
        root->left = deleteNode(root->left, data, deleted);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, deleted);
    else {
        deleted = true;
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else 
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = maxValueNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data, deleted);
        }
    }
    if (!root)
        return root;

    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    //RR
    if (balance > 1 && getBalance(root->right) >= 0)
        return rotateLeft(root);
    //RL
    if (balance > 1 && getBalance(root->right) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    //LL
    if (balance < -1 && getBalance(root->left) <= 0)
        return rotateRight(root);
    //LR
    if (balance < -1 && getBalance(root->left) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    return root;
}

bool searchNode(Node* node, long long data) {
    if (!node) return false;
    if (data == node->data) return true;
    else if (data < node->data)
        return searchNode(node->left, data);
    else 
        return searchNode(node->right, data);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Node* node = nullptr;

    for (int i = 0; i < n; i++) {
        char op;
        long long x;
        std::cin >> op >> x;
        switch(op) {
            case 'A': {
                bool duplicate = false;
                node = insertNode(node, x, duplicate);
                if (node) {
                    std::cout << getBalance(node) << "\n";
                } else {
                    std::cout << "0\n";
                }
                break;
            }
            case 'D' :{
                bool deleted = false;
                node = deleteNode(node, x, deleted);
                if (node) {
                    std::cout << getBalance(node) << "\n";
                } else {
                    std::cout << "0\n";
                }
                break;
            } 
            case 'C': {
                bool found = searchNode(node, x);
                if (found) {
                    std::cout << "Y\n";
                } else {
                    std::cout << "N\n";
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}