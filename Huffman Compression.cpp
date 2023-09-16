#include<iostream>
#include<string>
#include<unordered_map>
#include<queue>
using namespace std;

// Node structure for Huffman Tree
// huffmen tree Node
class Node {
public:
	char data;
	int frequency;   // here frequency = frequency 
	Node* left;
	Node* right;
	Node() {
		left = NULL;
		right = NULL;
	}
	Node(char name, int freq) {
		this->data = name;
		this->frequency = freq;
		left = NULL;
		right = NULL;
	}
};

// a messageNode : it gets transferred to the reveiver 
class messageNode {
public:
	string message;
	unordered_map<string, char> code;
	messageNode() {
		message = "";
		code.clear();
	}
	messageNode(string message , unordered_map<string, char> code ) {
		this->message = message;
		this->code = code;
	}
};

// frequency queue implementation for getting minimum frequency elements
class PriorityQueue {

	Node* pq[300];  // as we have only 256 characters in keyboard 
	int size;
public:
	PriorityQueue () {
		size = 0;
	}
	int getsize() {
		return size;
	}
	bool isEmpty() {
		return (size == 0);
	}
	Node* getmin() {
		return pq[0];
	}
	void insert(Node* element) {

		pq[size] = element;
		++size;
		int childindex = size - 1;

		while (childindex > 0) {
			int parentindex = (childindex - 1) / 2;
			if (pq[childindex]->frequency < pq[parentindex]->frequency) {
				Node* temp = pq[childindex];
				pq[childindex] = pq[parentindex];
				pq[parentindex] = temp;
			}
			else {
				break;
			}
			childindex = parentindex;
		}
	}
	void removeMin() {

		Node* ans = pq[0];
		pq[0] = pq[size - 1];
		--size;
		// downfy heap;
		int parentindex = 0;
		int leftchildindex = 2 * parentindex + 1;
		int rightchildindex = 2 * parentindex + 2;

		while (leftchildindex < size) {  // if not left child then 100% No right child;
			int minindex = parentindex;
			if (pq[minindex]->frequency > pq[leftchildindex]->frequency) {
				minindex = leftchildindex;
			}
			if (rightchildindex < size && pq[rightchildindex]->frequency < pq[minindex]->frequency) {
				minindex = rightchildindex;
			}
			if (minindex == parentindex) {
				break;
			}
			Node* temp = pq[minindex];
			pq[minindex] = pq[parentindex];
			pq[parentindex] = temp;
			parentindex = minindex;
			leftchildindex = 2 * parentindex + 1;
			rightchildindex = 2 * parentindex + 2;
		}

	}
};

class Huffman {
	Node* huffmanTreeRoot;
	unordered_map<char, string> code ; // code for ith character
	string message;
	string encoded_string;
	string decoded_string;

public:
	Huffman(string message ) {
		huffmanTreeRoot = NULL;
		this->message = message;
		encoded_string = "";
		decoded_string = "";
		code.clear();

		// creating huffman tree of given messsage 
		createHuffmanTree();
	}

private:
	void createHuffmanTree() {

		// storing frequency of every character
		unordered_map<char, int> frequency;

		for (char curr : message) {
			++frequency[curr];
		}

		// creating minheap
		PriorityQueue minheap;

		for (auto node : frequency ) {
			Node* currNode = new Node(node.first , node.second );
			minheap.insert(currNode);
		}

		// while size != 1 take two minimum put smallest on left and greater on right 
		while (minheap.getsize() != 1) {

			Node* leftNode = minheap.getmin();
			minheap.removeMin();
			Node* rightNode = minheap.getmin();
			minheap.removeMin();

			Node* topNode = new Node( '$', leftNode->frequency + rightNode->frequency );
			topNode->left = leftNode;
			topNode->right = rightNode;
			minheap.insert(topNode);
		}
		huffmanTreeRoot = minheap.getmin();
		extractCodes(huffmanTreeRoot); 
	}


	void extractCodes(Node* root, string s = "") {
		if (root == NULL) return;

		else if (root->data != '$') {  // it means we reach at leaf node .
			code[root->data] = s ;
			return;
		}
		extractCodes(root->left, s + "0");
		extractCodes(root->right, s + "1");
	}

public:
	messageNode encode(){
		if (huffmanTreeRoot == NULL) {
			cout << "Empty Message" << endl;
			return messageNode();
		}
		// Till now we've code for every character in string, so we can convert the given string into their following Huffman Code
		
		string encoded_string = "";
		for (char curr : message) {
			encoded_string += code[curr];
		}

		unordered_map<string, char> mp;
		for (auto it : code) {
			mp[it.second] = it.first;
		}
		return messageNode(encoded_string , mp );
	}

	string decode(messageNode encodedMessage){

		// Now that we've encoded string and now we got to take our string back, so we've their back code as well.
		string decoded_string = "";
		auto& code = encodedMessage.code;
		auto& encoded_string = encodedMessage.message;

		string temp = "";
		for (char curr : encoded_string){
			temp += curr ;
			if ( code.find(temp) != code.end()) {
				decoded_string += code[temp];
				temp = "";
			}
		}
		return decoded_string;
	}
};


int main(){

	cout << "Enter your message : ";
	string message;
	getline(cin, message);

	cout << message << endl;
	// Creating Huffman Tree
	Huffman * huffman = new Huffman(message) ;

	// getting our encoded message
	messageNode encodedMessage = huffman->encode();
	if (encodedMessage.message != "") {
		cout << encodedMessage.message<< endl;
	}
	for (auto it : encodedMessage.code) {
		cout << it.first << " " << it.second << endl;
	}
	// getting our decoded message
	// we can decode message at other end by getting our keys 
	string decoded_string = huffman->decode(encodedMessage);
	cout << decoded_string << endl;

	return 0;
}
