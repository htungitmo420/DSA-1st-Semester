#include <iostream>
#include <string>

struct Node {
    int data;
    int students;
    Node* left;
    Node* right;
    int height;
    Node(int key) {
        data = key;
        left = right = nullptr;
        height = 1;
        students = 0;
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

Node* insertNode(Node* node, int data, int student, bool& duplicate) {
    if (!node) {
        duplicate = false;
        Node* newNode = new Node(data);
        newNode->students |= (1 << (student - 1));
        return newNode;
    }
    if (data < node->data) {
        node->left = insertNode(node->left, data, student, duplicate);
    }
    else if (data > node->data) {
        node->right = insertNode(node->right, data, student, duplicate);
    }
    else {
        duplicate = true;
        node->students |= (1 << (student - 1));
        return node;
    }

    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
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

int stringToData(const std::string& s){
    int data = 0;
    for(char c : s){
        if('0' <= c && c <= '9') data = data * 62 + (c - '0');
        else if('A' <= c && c <= 'Z') data = data * 62 + (10 + c - 'A');
        else if('a' <= c && c <= 'z') data = data * 62 + (36 + c - 'a');
    }
    return data;
}

int countBits(int x){
    int count = 0;
    while(x){
        count += x & 1;
        x >>=1;
    }
    return count;
}

void traverseAndAssign(Node* node, int& total1, int& total2, int& total3){
    if (!node) return;
    traverseAndAssign(node->left, total1, total2, total3);
    int count = countBits(node->students);
    if(count ==1){
        if(node->students & 1)
            total1 +=3;
        else if(node->students & 2)
            total2 +=3;
        else if(node->students &4)
            total3 +=3;
    }
    else if(count ==2){
        if((node->students &1) && (node->students &2)){
            total1 +=1;
            total2 +=1;
        }
        if((node->students &1) && (node->students &4)){
            total1 +=1;
            total3 +=1;
        }
        if((node->students &2) && (node->students &4)){
            total2 +=1;
            total3 +=1;
        }
    }
    traverseAndAssign(node->right, total1, total2, total3);
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    Node* root = nullptr;

    for(int student=1; student<=3; ++student){
        for(int i=0; i<n; ++i){
            std::string file;
            std::cin >> file;
            int data = stringToData(file);
            bool duplicate = false;
            root = insertNode(root, data, student, duplicate);
        }
    }

    int total1 = 0, total2 = 0, total3 = 0;

    traverseAndAssign(root, total1, total2, total3);
    std::cout << total1 << " " << total2 << " " << total3;
    return 0;
}