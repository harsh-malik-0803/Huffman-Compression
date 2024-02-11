#include<iostream>
#include<string>
#include<unordered_map>
#include<queue>
#include "minHeap.cpp"
using namespace std;

// Node structure for Huffman Tree
// huffmen tree Node
class Node {
public:
	char data;
	int frequency;   // here frequency = frequency 
	Node* left, * right;
	Node() {
		left = right = nullptr;
	}
	Node(char name, int freq) {
		this->data = name;
		this->frequency = freq;
		Node();
	}
};

// a messageNode : it gets transferred to the reveiver 
class messageNode {
public:
	string message;
	unordered_map<string, char> code;
	messageNode() {}

	messageNode(string message, unordered_map<string, char> code) {
		this->message = message;
		this->code = code;
	}
};




class Huffman {

	Node* createHuffmanTree(string& message) {

		unordered_map<char, int> frequency;
		for (char curr : message) {
			++frequency[curr];
		}

		// creating minheap
		PriorityQueue<Node> minheap;

		for (auto node : frequency) {
			Node* currNode = new Node(node.first, node.second);
			minheap.insert(currNode);
		}

		while (minheap.getsize() > 1) {

			Node* leftNode = minheap.getmin();
			minheap.removeMin();
			Node* rightNode = minheap.getmin();
			minheap.removeMin();

			Node* topNode = new Node('$', leftNode->frequency + rightNode->frequency);
			topNode->left = leftNode;
			topNode->right = rightNode;
			minheap.insert(topNode);
		}
		return minheap.getmin();
	}


	void extractCodes(Node* root, unordered_map<char, string>& code, string s = "") {
		if (root == nullptr) return;

		else if (root->data != '$') {
			code[root->data] = s;
			return;
		}

		extractCodes(root->left, code, s + "0");
		extractCodes(root->right, code, s + "1");
	}

public:

	Huffman() {}

	messageNode encode(string message) {

		Node* huffmanTreeRoot = createHuffmanTree(message);
		unordered_map<char, string  > code;
		extractCodes(huffmanTreeRoot, code);

		if (code.size() == 0) {
			cout << "Empty Message" << endl;
			return messageNode();
		}

		string encoded_string;
		for (char curr : message) {
			encoded_string += code[curr];
		}

		unordered_map<string, char> charTocode;
		for (auto it : code) {
			charTocode[it.second] = it.first;
		}
		return messageNode(encoded_string, charTocode);
	}

	string decode(string message, unordered_map<string, char> code) {

		string decoded_string;
		string temp = "";
		for (char curr : message) {
			temp += curr;
			if (code.find(temp) != code.end()) {
				decoded_string += code[temp];
				temp = "";
			}
		}
		return decoded_string;
	}

	~Huffman() {

	}
};