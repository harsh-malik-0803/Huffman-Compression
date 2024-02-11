#include<iostream> // input output stream
#include <string>
#include "huffmanCompression.cpp"
using namespace std;


int main() {
	
	// Creating Huffman Tree
	Huffman* huffman = new Huffman();

	cout << "Enter your message : ";
	string message;
	getline(cin, message);
	cout << "Given message : " << message << endl;


	// getting our encoded message with code
	messageNode encodedMessage = huffman->encode(message);
	if (encodedMessage.message != "") {
		cout << "Encoded Message : " << encodedMessage.message << endl;
	}

	// getting our decoded message
	// we can decode message at other end by using keys
	string decoded_string = huffman->decode(encodedMessage.message, encodedMessage.code);
	cout << "Decoded Message : " << decoded_string << endl;

	delete huffman;

	return 0;
}