#include <iostream>
#include <string>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int key) {
        data = key;
        left = right = nullptr;
        height = 1;
    }
};

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) {
    return node ? node->height : 0;
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

Node* insertNode(Node* node, int key, bool& duplicate) {
    if (!node) {
        duplicate = false;
        return new Node(key);
    }

    if (key < node->data) {
        node->left = insertNode(node->left, key, duplicate);
    }
    else if (key > node->data) {
        node->right = insertNode(node->right, key, duplicate);
    }
    else {
        duplicate = true;
        return node;
    }

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    int balance = getBalance(node);
    //RR
    if (balance > 1 && key > node->right->data)
        return rotateLeft(node);
    //RL
    if (balance > 1 && key < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    //LL
    if (balance < -1 && key < node->left->data)
        return rotateRight(node);
    //LR
    if (balance < -1 && key > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

int countUniqueChar(const std::string& s) {
    long long mask = 0;
    for(char c : s){
        if('0' <= c && c <= '9'){
            mask |= (1ULL << (c - '0'));
        }
        else if('A' <= c && c <= 'Z'){
            mask |= (1ULL << (10 + c - 'A'));
        }
        else if('a' <= c && c <= 'z'){
            mask |= (1ULL << (36 + c - 'a'));
        }
    }
    int count = 0;
    while(mask){
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    long long total = 0;
    Node* root = nullptr;

    for(int i = 0; i < n; ++i){
        std::string contact;
        std::cin >> contact;

        bool duplicate = false;
        int key = 0;
        for(char c : contact){
            key = key * 62 + (
                ('0' <= c && c <= '9') ? (c - '0') :
                ('A' <= c && c <= 'Z') ? (10 + c - 'A') :
                ('a' <= c && c <= 'z') ? (36 + c - 'a') :
                0
            );
        }

        root = insertNode(root, key, duplicate);

        if(duplicate){
            int M = countUniqueChar(contact);
            total += M;
        }
    }

    std::cout << total;
    return 0;
}