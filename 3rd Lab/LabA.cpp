#include <iostream>

struct Node {
    int data;
    Node* next;
};

typedef Node* node;

bool Empty(node top) {
    return top == NULL;
}

node NewNode(int x) {
    node temp = new Node();
    temp->data = x;
    temp->next = NULL;
    return temp;
}

void pop(node& top) {
    if (top == NULL) {
        return;
    }
    node temp = top;
    top = top->next;
    delete temp;
}

void push(node& top, int x) {
    node temp = NewNode(x);
    temp->next = top;
    top = temp;
}


int GetTop(node top) {
    if (top != NULL) {
        return top->data;
    }
    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(NULL);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    char operation;
    int x;
    node top = NULL;

    for (int i = 1; i <= n; i++) {
        std::cin >> operation;
        if (operation == '+') {
            std::cin >> x;
            push(top, x);
        } else if (operation == '-') {
            if (!Empty(top)) {
                std::cout << GetTop(top) << "\n";
                pop(top);
            }
        }
    }
    while (!Empty(top)) {
        pop(top);
    }
    return 0;
}


// #include <iostream>
// #include <stack>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;
//     char add;
//     int x;
//     stack<int> s;

//     for (unsigned int i = 1; i <= n; i++) {
//         cin >> add;
//         if (add == '+') {
//             cin >> x;
//             s.push(x);
//         } else {
//             if (!s.empty()) {
//                 cout << s.top() << endl;
//                 s.pop();
//             }
//         }
//     }

//     return 0;
// }
