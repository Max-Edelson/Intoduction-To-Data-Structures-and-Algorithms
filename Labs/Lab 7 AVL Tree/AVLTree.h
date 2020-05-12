#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <iostream>

using namespace std;

class AVLTree {
	private:
		Node* root;

	public:
		void insert(const string &);
		int balanceFactor(Node*);
		void printBalanceFactors();
		void visualizeTree(const string &);
		void print();
		AVLTree();

	private:
		int returnHeight(Node*) const;
		int height(Node*) const;
		int max(int, int) const;
		Node* findUnbalanceNode();
		void AVLTreeRebalance(Node*);
		void rotate(Node*);
		void rotateLeft(Node*);
		void rotateRight(Node*);
		void printBalanceFactors(Node*);
		void visualizeTree(ofstream &, Node*);
		void printInOrder(Node*);
};

#endif
