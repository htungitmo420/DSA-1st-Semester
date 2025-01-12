#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int data;
    int left;
    int right;
    int height;
};

std::vector<Node> tree;

int getHeight(int v) {
    return v == -1 ? 0 : tree[v].height;
}

void updateHeight(int v) {
    int hl = getHeight(tree[v].left);
    int hr = getHeight(tree[v].right);
    tree[v].height = (hl > hr ? hl : hr) + 1;
}

int rotateRight(int v) {
    int u = tree[v].left;
    tree[v].left = tree[u].right;
    tree[u].right = v;
    updateHeight(v);
    updateHeight(u);
    return u;
}

int rotateLeft(int v) {
    int u = tree[v].right;
    tree[v].right = tree[u].left;
    tree[u].left = v;
    updateHeight(v);
    updateHeight(u);
    return u;
}

int balance(int v) {
    updateHeight(v);
    int b = getHeight(tree[v].right) - getHeight(tree[v].left);
    if (b == 2) {
        if (getHeight(tree[tree[v].right].right) < getHeight(tree[tree[v].right].left)) {
            tree[v].right = rotateRight(tree[v].right);
        }
        return rotateLeft(v);
    }
    if (b == -2) {
        if (getHeight(tree[tree[v].left].left) < getHeight(tree[tree[v].left].right)) {
            tree[v].left = rotateLeft(tree[v].left);
        }
        return rotateRight(v);
    }
    return v;
}

int insert(int v, int data) {
    std::vector<int> path;
    int curr = v;
    int parent = -1;

    while (curr != -1) {
        path.push_back(curr);
        parent = curr;
        if (data < tree[curr].data) {
            curr = tree[curr].left;
        } else {
            curr = tree[curr].right;
        }
    }

    Node newNode = {data, -1, -1, 1};
    tree.push_back(newNode);
    int newIndex = tree.size() - 1;

    if (parent == -1) {
        v = newIndex;
    } else if (data < tree[parent].data) {
        tree[parent].left = newIndex;
    } else {
        tree[parent].right = newIndex;
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        int node = path[i];
        node = balance(node);

        if (i > 0) {
            int prev = path[i - 1];
            if (tree[prev].left == path[i]) {
                tree[prev].left = node;
            } else {
                tree[prev].right = node;
            }
        } else {
            v = node;
        }
    }

    return v;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    int root = -1;
    if (n > 0) {
        tree.resize(n);
        for (int i = 0; i < n; ++i) {
            int data, left, right;
            std::cin >> data >> left >> right;
            tree[i] = {data, left - 1, right - 1, 1};
        }
        root = 0;

        for (int i = n - 1; i >= 0; --i) {
            updateHeight(i);
        }
    }

    int x;
    std::cin >> x;

    root = insert(root, x);

    std::vector<int> newIndex(tree.size(), -1);
    std::vector<Node> newTree;
    std::queue<int> q;
    int currIndex = 0;

    q.push(root);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == -1) continue;
        if (newIndex[v] != -1) continue;
        newIndex[v] = currIndex++;
        newTree.push_back(tree[v]);
        q.push(tree[v].left);
        q.push(tree[v].right);
    }

    std::cout << newTree.size() << std::endl;
    for (size_t i = 0; i < newTree.size(); ++i) {
        int left = newTree[i].left == -1 ? 0 : newIndex[newTree[i].left] + 1;
        int right = newTree[i].right == -1 ? 0 : newIndex[newTree[i].right] + 1;
        std::cout << newTree[i].data << " " << left << " " << right << std::endl;
    }

    return 0;
}
