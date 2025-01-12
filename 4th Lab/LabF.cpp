#include <iostream>
#include <vector>
#include <stack>
#include <string>

struct Node {
    long long data;
    Node* left;
    Node* right;
    Node* parent;
    long long max;
    long long min;
    long long dp;

 Node(long long key) {
        data = key;
        max = key;
        min = key;
        dp = key;
        left = right = parent = nullptr;
    }
};

void updateSubtreeValues(Node* node) {
    if (!node) return;

    node->dp = node->data;
    node->max = node->data;
    node->min = node->data;

    bool isBST = true;

    if (node->left) {
        updateSubtreeValues(node->left);
        if (node->left->dp == -1e9 || node->left->max >= node->data) {
            isBST = false;
        } else {
            node->dp += node->left->dp;
            node->min = std::min(node->min, node->left->min);
        }
    }

    if (node->right) {
        updateSubtreeValues(node->right);
        if (node->right->dp == -1e9 || node->right->min <= node->data) {
            isBST = false;
        } else {
            node->dp += node->right->dp;
            node->max = std::max(node->max, node->right->max);
        }
    }

    if (!isBST) {
        node->dp = -1e9;
    }
}

long long calculateMaxBSTSum (Node* root) {
    if (!root) return 0;
    updateSubtreeValues(root);

    std::stack<Node*> nodes;
    nodes.push(root);
    long long maxSum = 0;

    while (!nodes.empty()) {
     Node* node = nodes.top();
        nodes.pop();
        if (node->dp != -1e9) {
            maxSum = std::max(maxSum, node->dp);
        }
        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
    }
    return maxSum;
}

signed main() {
    std::string input;
    getline(std::cin, input);

    Node* root = nullptr;
    Node* current = nullptr;
    std::stack<Node*> nodeStack;

    long long index = 0;

    for (int i = 0; i < (long long)input.size(); ++i) {
        char command = input[i];
        if (command == 'l' || command == 'r') {
            if (!nodeStack.empty()) {
                current = nodeStack.top();
            }
            index++;
         Node* newNode = new Node(0);
            newNode->parent = current;
            if (command == 'l') {
                current->left = newNode;
            } else {
                current->right = newNode;
            }
            nodeStack.push(newNode);
            current = newNode;
        } else if (command == 'u') {
            if (!nodeStack.empty()) {
                nodeStack.pop();
                if (!nodeStack.empty()) {
                    current = nodeStack.top();
                }
            }
        } else if (isdigit(command) || command == '-' || command == '+') {
            long long value = 0;
            long long sign = 1;
            if (command == '-') {
                sign = -1;
                ++i;
            } else if (command == '+') {
                ++i;
            }

            while (i < input.size() && isdigit(input[i])) {
                value = value * 10 + (input[i] - '0');
                ++i;
            }
            --i;
            value *= sign;

            if (current) {
                current->data = value;
                current->dp = value;
                current->max = value;
                current->min = value;
            } else {
                root = new Node(value);
                nodeStack.push(root);
                current = root;
            }
        }
    }

    long long maxSum = calculateMaxBSTSum(root);
    std::cout << maxSum << std::endl;

    std::stack<Node*> cleanupStack;
    cleanupStack.push(root);
    while (!cleanupStack.empty()) {
     Node* node = cleanupStack.top();
        cleanupStack.pop();
        if (node->left) cleanupStack.push(node->left);
        if (node->right) cleanupStack.push(node->right);
        delete node;
    }

    return 0;
}