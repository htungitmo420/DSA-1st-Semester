#include <iostream>

struct Node {
    int data;
    Node* next;
};

bool Empty(Node* top) {
    return top == NULL;
}

void push(Node* &top, int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

void pop(Node* &top) {
    if (top == NULL) {
        return;
    }
    Node* temp = top;
    top = top->next;
    delete temp;
}

int peek(Node* top) {
    if (Empty(top)) {
        return -1;
    }
    return top->data;
}

long maximum_rectangle_area(int h[], int n) {
    long maximum_area = 0;
    Node* top = NULL;
    for (int i = 0; i < n; i++) {
        while (!Empty(top) && h[peek(top)] >= h[i]) {
            int height = h[peek(top)];
            pop(top);
            int width = Empty(top) ? i : i - peek(top) - 1;
            maximum_area = std::max(maximum_area, (long)height * width);
        }
        push(top, i);
    }

    while (!Empty(top)) {
        int height = h[peek(top)];
        pop(top);
        int width = Empty(top) ? n : n - peek(top) - 1;
        maximum_area = std::max(maximum_area, (long) height * width);
    }

    return maximum_area;
}

int main() {
    int n;
    std::cin >> n;
    int* h = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }

    std::cout << maximum_rectangle_area(h, n) << std::endl;
    return 0;
}