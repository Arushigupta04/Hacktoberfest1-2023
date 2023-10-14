#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void buildHuffmanTree(string text) {
    map<char, int> frequency_map;
    for (char c : text) {
        frequency_map[c]++;
    }

    priority_queue<Node*, vector<Node*>, CompareNodes> pq;
    for (auto pair : frequency_map) {
        Node* node = new Node(pair.first, pair.second);
        pq.push(node);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();
    // Build and print the Huffman codes
    map<char, string> huffman_codes;
    string code;
    buildHuffmanCodes(root, code, huffman_codes);

    cout << "Huffman Codes:\n";
    for (auto pair : huffman_codes) {
        cout << pair.first << " : " << pair.second << endl;
    }
}

void buildHuffmanCodes(Node* root, string code, map<char, string>& huffman_codes) {
    if (!root) {
        return;
    }
    
    if (root->data != '$') {
        huffman_codes[root->data] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffman_codes);
    buildHuffmanCodes(root->right, code + "1", huffman_codes);
}

int main() {
    string text = "this is an example for huffman encoding";
    buildHuffmanTree(text);

    return 0;
}
