# Huffman Compression

# Why Huffman Compression?
Everybody loves compression.

Ques : The number of photos we can store on our smartphone?

Ans : It depends on how much we can compress the files with little or no loss. 

The time required to download a file? The more we compress, the faster the download. 

Huffman coding is a widely-used method for lossless compression. 
For example, every time we import or export an MP3 audio file, our computer uses Huffman codes.

# What is Huffman Compression ?
Huffman Coding is a lossless data compression algorithm where each character in the data is assigned a variable length prefix code. The least frequent character gets the largest code and the most frequent one gets the smallest code. 

Encoding the data using this technique is very easy and efficient.

However, decoding the bitstream generated using this technique is inefficient.Decoders(or Decompressors)require the knowledge of the encoding mechanism used in order to decode the encoded data back to the original characters. Hence information about the encoding process needs to be passed to the decoder along with the encoded data as a table of characters and their corresponding codes. In regular Huffman coding of a large data, this table takes up a lot of memory space and also if a large no. of unique characters are present in the data then the compressed(or encoded) data size increases because of the presence of the codebook.

# Steps to build Huffman Tree
1. Input is an array of unique characters along with their frequency of occurrences and output is Huffman Tree.

2. Create a leaf node for each unique character and build a min heap of all leaf nodes (Min Heap is used as a priority queue. The value of frequency field is used to compare two nodes in min heap. Initially, the least frequent character is at root)

3. Extract two nodes with the minimum frequency from the min heap.
   
4. Create a new internal node with a frequency equal to the sum of the two nodes frequencies. Make the first extracted node as its left child and the other extracted node as its right child. Add this node to the min heap.
 
5. Repeat steps#2 and #3 until the heap contains only one node. The remaining node is the root node and the tree is complete.

# Time complexity: O(nlogn) 
Here n is the number of unique characters. If there are n nodes, extractMin() is called 2*(n – 1) times. extractMin() takes O(logn) time as it calls minHeapify(). So, the overall complexity is O(nlogn).

# Compression
Do compression of 20%-90% depend on  the data. If frequency of all characters are nearly same than compression is less.   
