//Code mẫu tham khảo
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    struct compare {
        bool operator()(Node* l, Node* r) {
            return l->freq > r->freq;
        }
    };
};

Node* buildHuffmanTree(const vector<pair<char, int>>& freqVec) {
    priority_queue<Node*, vector<Node*>, Node::compare> pq;

    for (const auto& pair : freqVec) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* internalNode = new Node('\0', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;
        pq.push(internalNode);
    }

    return pq.top();
}

void generateHuffmanCodes(Node* root, string str, vector<pair<char, string>>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        bool found = false;
        for (auto& p : huffmanCode) {
            if (p.first == root->ch) {
                p.second = str;
                found = true;
                break;
            }
        }
        if (!found) {
           huffmanCode.push_back({root->ch, str});
        }

        return;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCode);
    generateHuffmanCodes(root->right, str + "1", huffmanCode);
}

string encode(const string& text, const vector<pair<char, string>>& huffmanCode) {
    string encodedText = "";
    for (char ch : text) {
        for(const auto& p : huffmanCode){
            if(p.first == ch){
                encodedText += p.second;
                break;
            }
        }
    }
    return encodedText;
}


string decode(const string& encodedText, Node* root) {
    string decodedText = "";
    Node* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}


int main() {
    string text = "A_DEAD_DAD_CEDED_A_BAD_BABE_A_BEADED_ABACA_BED";

    vector<pair<char, int>> freqVec;
    for (char ch : text) {
         bool found = false;
        for(auto& p : freqVec){
            if(p.first == ch){
                p.second++;
                found = true;
                break;
            }
        }
        if(!found){
            freqVec.push_back({ch, 1});
        }
    }

    Node* root = buildHuffmanTree(freqVec);


    vector<pair<char, string>> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    cout << "Huffman Codes:" << endl;
    for (const auto& p : huffmanCode) {
         cout << p.first << ": " << p.second << endl;
    }

    string encodedText = encode(text, huffmanCode);
    cout << "\nEncoded text: " << encodedText << endl;

    string decodedText = decode(encodedText, root);
    cout << "Decoded text: " << decodedText << endl;

    return 0;
}