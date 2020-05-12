#include "AVLTree.h"

#include <iostream>
#include <fstream>

using namespace std;

AVLTree::AVLTree() : root(0) {}

void AVLTree::insert(const string &input) {
	Node* node = new Node(input);
	
	if (!root) {
		root = node;
	}
	else {
		Node* cur = root;
		
		while (cur) {
			if (node->data == cur->data) { return; }
			else if (node->data < cur->data) {
				if (!cur->left) {
					cur->left = node;
					node->parent = cur;
					cur = nullptr;
				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (!cur->right) {
					cur->right = node;
					node->parent = cur;
					cur = nullptr;
				}
				else {
					cur = cur->right;
				}
			}
		}

//		print();

		node = node->parent;
		
		while (node) {
			rotate(node);
			node = node->parent;
		}
	}
}

int AVLTree::max(int left, int right) const {

	int val = right;
	
	if (left > right)
		val = left;
	return val;
}

int AVLTree::height(Node* node) const {
	if (!node)
		return 0;

	int left = height(node->left);
	int right = height(node->right);

	return 1 + max(left, right);
}

int AVLTree::balanceFactor(Node* node) {
	return height(node->left) - height(node->right);
}

void AVLTree::printBalanceFactors() {
	printInOrder(root);
}

void AVLTree::printInOrder(Node* node) {
	if (!node)
		return;

	printInOrder(node->left);
	cout << node->data << '(' << balanceFactor(node) << "), ";
	printInOrder(node->right);
}

static void nodePrint(const Node* node, int level) {
        cout << "*";
        for (int i = 0; i < level; i++)
                cout << "       ";

        if (!node) {
                cout << "NULL" << endl;
                return;
        }

        cout << node->data << endl;;
        nodePrint(node->left, level + 1);
        nodePrint(node->right, level + 1);

}

void AVLTree::print() {
	nodePrint(root, 0);
}

void AVLTree::rotate(Node* node) {
	if (balanceFactor(node) <= -2) {
		if (balanceFactor(node->right) == 1) {
//			cout << "double rotate: rotated right on " << node->right->data << endl;
			rotateRight(node->right);
		}
//		print();
//		cout << "rotating left on: " << node->data << endl;
		rotateLeft(node);
	}
	else if (balanceFactor(node) >= 2) {
		if (balanceFactor(node->left) == -1) {
			rotateLeft(node->left);
		}
		rotateRight(node);
	}
}

void AVLTree::rotateLeft(Node* node) {
	Node* rightLeftChild = node->right->left;

	if (!node->parent) {
		root = node->right;
		root->parent = nullptr;
		root->left = node;

		node->right = rightLeftChild;
	}
	else {
		Node* parentNode = node->parent;
		Node* newSubroot = node->right;

		if (parentNode->right == node) {
			parentNode->right = node->right;
		}
		else {
			parentNode->left = node->right;
		}

		newSubroot->parent = node->parent;
		node->parent = newSubroot;
		node->right = rightLeftChild;
		newSubroot->left = node;
	}
}

void AVLTree::rotateRight(Node* node) {
        Node* leftRightChild = node->left->right;

        if (!node->parent) { 
                root = node->left;
                root->parent = nullptr;
                root->right = node;

                node->left = leftRightChild;
        }
        else {
                Node* parentNode = node->parent;
		Node* newSubroot = node->left;

                if (parentNode->left == node) {
                        parentNode->left = node->left;
                }
                else {  
                        parentNode->right = node->left;
                }

                newSubroot->parent = parentNode;
                node->parent = newSubroot;
                node->left = leftRightChild;
		newSubroot->right = node;
        }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}
