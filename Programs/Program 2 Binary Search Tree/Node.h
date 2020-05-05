#ifndef NODE_H
#define NODE_H

class Node {
	
	public:
		string data;
		int occurances;
		Node* left;
		Node* right;
		Node(string);
};

#endif
