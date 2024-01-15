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
	Node* left , * right ;
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

	messageNode(string message , unordered_map<string, char> code ) {
		this->message = message;
		this->code = code;
	}
};

template<typename T>
class PriorityQueue {
	
	T* m_data[300];  // as we have only 256 characters in keyboard 
	int m_size;

public:
	PriorityQueue () {
		m_size = 0;
	}
	int getsize() {
		return m_size;
	}
	bool isEmpty() {
		return m_size == 0;
	}
	T* getmin() {
		if (isEmpty()) {
			cout << "Empty Queue" << endl;
			return nullptr;
		}
		return m_data[0];
	}

private:
	void swap(T** data1, T** data2) {
		T * temp = *data1;
		*data1 = *data2;
		*data2 = temp; 
	}

public:

	void insert( T* element) {

		m_data[m_size] = element;
		++m_size;
		int childindex = m_size - 1;

		while (childindex > 0) {
			int parentindex = (childindex - 1) / 2;
			if (m_data[childindex]->frequency < m_data[parentindex]->frequency) {
				swap(&m_data[childindex], &m_data[parentindex]);
			}
			else {
				break;
			}
			childindex = parentindex;
		}
	}
	void removeMin() {

		T* ans = m_data[0];
		m_data[0] = m_data[m_size - 1];
		--m_size;

		// downfy heap;
		int parentindex = 0;
		int leftchildindex = 2 * parentindex + 1;
		int rightchildindex = 2 * parentindex + 2;

		while (leftchildindex < m_size) {  // if not left child then 100% No right child;
			int minindex = parentindex;
			if (m_data[minindex]->frequency > m_data[leftchildindex]->frequency) {
				minindex = leftchildindex;
			}
			if (rightchildindex < m_size && m_data[rightchildindex]->frequency < m_data[minindex]->frequency) {
				minindex = rightchildindex;
			}
			if (minindex == parentindex) {
				break;
			}
			swap( &m_data[minindex] , &m_data[parentindex]);
			
			parentindex = minindex;
			leftchildindex = 2 * parentindex + 1;
			rightchildindex = 2 * parentindex + 2;
		}

	}
};


class Huffman {
	
	Node * createHuffmanTree(string &message ) {

		unordered_map<char, int> frequency;
		for (char curr : message) {
			++frequency[curr];
		}

		// creating minheap
		PriorityQueue<Node> minheap;

		for (auto node : frequency ) {
			Node* currNode = new Node(node.first , node.second );
			minheap.insert(currNode);
		}

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
		return minheap.getmin();
	}


	void extractCodes(Node* root, unordered_map<char , string>& code , string s = "") {
		if (root == nullptr) return;

		else if (root->data != '$') {
			code[root->data] = s ;
			return;
		}

		extractCodes(root->left, code , s + "0");
		extractCodes(root->right, code , s + "1");
	}

public:

	Huffman() {}

	messageNode encode(string message ){

		Node * huffmanTreeRoot = createHuffmanTree(message);
		unordered_map<char , string  > code;
		extractCodes(huffmanTreeRoot , code );

		if (code.size() == 0 ) {
			cout << "Empty Message" << endl;
			return messageNode();
		}

		string encoded_string ;
		for (char curr : message) {
			encoded_string += code[curr];
		}

		unordered_map<string, char> charTocode;
		for (auto it : code) {
			charTocode[it.second] = it.first;
		}
		return messageNode(encoded_string , charTocode );
	}

	string decode(string message , unordered_map<string, char> code ){

		string decoded_string;
		string temp = "";
		for (char curr : message ){
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

	
	// Creating Huffman Tree
	Huffman * huffman = new Huffman() ;

	cout << "Enter your message : ";
	string message;
	getline(cin, message);
	cout << "Given message : " <<message << endl;


	// getting our encoded message with code 
	messageNode encodedMessage = huffman->encode(message);
	if (encodedMessage.message != "") {
		cout <<"Encoded Message : "<< encodedMessage.message << endl;
	}
	
	// getting our decoded message
	// we can decode message at other end by using keys 
	string decoded_string = huffman->decode(encodedMessage.message , encodedMessage.code );
	cout << "Decoded Message : " << decoded_string << endl;

	return 0;
}