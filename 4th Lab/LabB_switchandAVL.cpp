#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
    int height;

    Node (int key) {
        data = key;
        left = right = nullptr;
        height = 1;
    }
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

void fixHeight(Node* node) {
    int r = getHeight(node->right);
    int l = getHeight(node->left);
    node->height = (l > r ? l : r) + 1;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rotateLeft(Node* root){
    Node *p = root->right;
    root->right = p->left;
    p->left = root;
    fixHeight(root);
    fixHeight(p);
    return p;
}

Node* rotateRight(Node* root){
    Node *p = root->left;
    root->left = p->right;
    p->right = root;
    fixHeight(root);
    fixHeight(p);
    return p;
}

Node* insertNode(Node* root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insertNode(root->left,data);
    } else {
        root->right = insertNode(root->right,data);
    }

    fixHeight(root);
    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data) return rotateRight(root);
    if (balance < -1 && data > root->right->data) return rotateLeft(root);
    if (balance > 1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
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

Node* deleteNode(Node* root, int target) {
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
        Node* succ = successor(root);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    
    if (root == nullptr) return root;
    fixHeight(root);
    int balance = getBalance(root);
    
    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

bool NodeExist(Node* root, int target) {
    while (root != nullptr) {
        if (root->data == target) return true;
        root = (target < root->data) ? root->left : root->right;
    }
    return false;
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