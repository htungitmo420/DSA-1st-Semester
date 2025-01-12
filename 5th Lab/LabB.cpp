#include <iostream> 
#include <vector>
#include <stack>
#include <queue>

struct Node {
    int key;
    int left;
    int right;
};

std::vector<Node> tree;
std::vector<int> heights;

void getHeights(int root) {
    std::stack<int> s;
    std::vector<bool> visited(tree.size(), false);
    s.push(root);

    while (!s.empty()) {
        int v = s.top();

        if (v == -1) {
            s.pop();
            continue;
        }

        if (visited[v]) {
            s.pop();
            int hl = tree[v].left == -1 ? 0 : heights[tree[v].left];
            int hr = tree[v].right == -1 ? 0 : heights[tree[v].right];
            heights[v] = (hl > hr ? hl : hr) + 1;
        } else {
            visited[v] = true;
            s.push(v);
            if (tree[v].right != -1) s.push(tree[v].right);
            if (tree[v].left != -1) s.push(tree[v].left);
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    tree.resize(n);
    heights.resize(n, 0);

    for (int i = 0; i < n; i++) {
        int key, left, right;
        std::cin >> key >> left >> right;
        tree[i].key = key;
        tree[i].left = left ? left - 1 : -1;
        tree[i].right = right ? right - 1 : -1;
    }

    int root = 0;

    getHeights(root);

    int hl = tree[root].left == -1 ? 0 : heights[tree[root].left];
    int hr = tree[root].right == -1 ? 0 : heights[tree[root].right];
    int balance = hr - hl;

    int rightChild = tree[root].right;
    int hrl = tree[rightChild].left == -1 ? 0 : heights[tree[rightChild].left];
    int hrr = tree[rightChild].right == -1 ? 0 : heights[tree[rightChild].right];
    int rightBalance = hrr - hrl;

    if (rightBalance < 0) { //Big left
        int right = tree[root].right;
        int rightLeft = tree[right].left;

        int rightLeftLeft = tree[rightLeft].left;
        int rightLeftRight = tree[rightLeft].right;

        tree[rightLeft].left = root;
        tree[rightLeft].right = right;

        tree[root].right = rightLeftLeft;
        tree[right].left = rightLeftRight;

        root = rightLeft;
    } else { //Small left
        int right = tree[root].right;
        int rightLeft = tree[right].left;

        tree[right].left = root;
        tree[root].right = rightLeft;

        root = right;
    }
    
    std::vector<int> newIndex(tree.size(), -1);
    std::vector<Node> newTree;
    std::queue<int> q;
    int index = 0;

    q.push(root);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v == -1) continue;
        if (newIndex[v] != -1) continue;
        newIndex[v] = index++;
        newTree.push_back(tree[v]);
        q.push(tree[v].left);
        q.push(tree[v].right);
    }

    std::cout << n << std::endl;
    for (int i = 0; i < n; i++) {
        int left = newTree[i].left == -1 ? 0 : newIndex[newTree[i].left] + 1;
        int right = newTree[i].right == -1 ? 0 : newIndex[newTree[i].right] + 1;
        std::cout << newTree[i].key << " " << left << " " << right << std::endl;
    }

    return 0;
}