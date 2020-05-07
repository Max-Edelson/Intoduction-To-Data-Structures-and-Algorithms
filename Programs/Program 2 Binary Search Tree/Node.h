#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
	
	public:
		string data;
		int occurances;
		Node* left;
		Node* right;
		Node(string);
};

#endif
