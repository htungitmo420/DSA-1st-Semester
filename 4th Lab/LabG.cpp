#include <iostream>
#include <vector>

std::vector<int> output;

struct Node {
    int data;
    Node* right;
    Node* left;
    Node(int key) {
        data = key;
        right = left = nullptr;
    }
};

Node* insertNode(Node* root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
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
    return root;
}

void inOrder(Node* node) {
    if (node == nullptr) return;
    inOrder(node->left);
    output.push_back(node->data);
    inOrder(node->right);
}

void convertInOrderToVec(Node* root, std::vector<int>& result) {
    if (root == nullptr) return;
    convertInOrderToVec(root->left, result);
    result.push_back(root->data);
    convertInOrderToVec(root->right, result);
}

std::vector<int> mergeVectors(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    std::vector<int> merged;
    int i = 0, j = 0;

    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            if (merged.size() > 0 && vec1[i] != merged.back()) merged.push_back(vec1[i]);
            if (merged.size() == 0) merged.push_back(vec1[i]);
            i++;
        } else {
            if (merged.size() > 0 && vec2[j] != merged.back()) merged.push_back(vec2[j]);
            if (merged.size() == 0) merged.push_back(vec2[j]);
            j++;
        }
    }
    while (i < vec1.size()) {
        if (merged.size() > 0 && vec1[i] != merged.back()) merged.push_back(vec1[i]);
        if (merged.size() == 0) merged.push_back(vec1[i]);
        i++;
    }
    while (j < vec2.size()) {
        if (merged.size() > 0 && vec2[j] != merged.back()) merged.push_back(vec2[j]);
        if (merged.size() == 0) merged.push_back(vec2[j]);
        j++;
    }
    return merged;
}

Node* sortedArrayToBST(const std::vector<int>& arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    Node* root = new Node(arr[mid]);
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);
    return root;
}

void deleteTask(Node* root) {
    if (root == nullptr) return;
    deleteTask(root->left);
    deleteTask(root->right);
    delete root;
}

void mergeAndRebuild(Node*& rootNiko, Node*& rootStepan) {
    std::vector<int> nikoTasks, stepanTasks, mergedTasks;
    convertInOrderToVec(rootNiko, nikoTasks);
    convertInOrderToVec(rootStepan, stepanTasks);
    rootStepan = NULL;
    mergedTasks = mergeVectors(nikoTasks, stepanTasks);
    rootNiko = sortedArrayToBST(mergedTasks, 0, mergedTasks.size() - 1);
    output.clear();
    inOrder(rootNiko);
    for (int i = 0; i < (int)output.size(); i++){
        std::cout << output[i];
        if (i < ((int)output.size() - 1)) std::cout << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    Node* tasksNiko = nullptr;
    Node* tasksStep = nullptr;

    for (int i = 0; i < n; i++) {
        int cmd;
        std::cin >> cmd;

        switch(cmd) {
            case 0: {
                int ID, tasks;
                std::cin >> ID >> tasks;
                if (ID == 0) {
                    tasksNiko = insertNode(tasksNiko, tasks);
                } else if (ID == 1) {
                    tasksStep = insertNode(tasksStep, tasks);
                }
                break;
            }
            case 1: {
                int ID, tasks;
                std::cin >> ID >> tasks;
                if (ID == 0) {
                    tasksNiko = deleteNode(tasksNiko, tasks);
                } else if (ID == 1) {
                    tasksStep = deleteNode(tasksStep, tasks);
                }
                break;
            }
            case 2:
                mergeAndRebuild(tasksNiko, tasksStep);
                break;
        }
    }
    return 0;
}