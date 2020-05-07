#include "BSTree.h"

#include <iostream>

using namespace std;

BSTree::BSTree() : root(nullptr) {}

BSTree::~BSTree() {
	//deleteNodes(root);
	//root = nullptr;
}

void BSTree::deleteNodes(Node* node) {
	if (node) {
		deleteNodes(node->left);
		deleteNodes(node->right);
		delete node;
	}
}

void BSTree::insert(const string &newString) {
	Node* temp = root;

	if (!temp) {
		root = new Node(newString);
	}
	else {
		while (temp) {
			if (temp->data == newString) {
				temp->occurances++;
				break;
			}
			else if (newString < temp->data) {
				if (!temp->left) {
					temp->left = new Node(newString);
					temp = nullptr;
				}
				else {
					temp = temp->left;
				}
			}
			else {
				if (!temp->right) {
					temp->right = new Node(newString);
					temp = nullptr;
				}
				else {
					temp = temp->right;
				}
			}
		} 
	}
}

void BSTree::remove(const string &key) {
	Node* par = nullptr;
	Node* cur = root;

	while (cur) {
		if (cur->data == key) {
			if (!cur->left && !cur->right) {
				//leaf node
				if (cur->occurances == 1) {
					if (!par) {
						//cur is root
						delete cur;
						root = nullptr;
					}
					else if (par->left == cur) {
						par->left = nullptr;
					}
					else {
						par->right = nullptr;
					}
				}
				else {
					cur->occurances--;
				}
			}
			else if (cur->left && !cur->right) {
				 if (cur->occurances == 1) {
                                        if (!par) {
                                                //cur is root
                                                root = cur->left;
                                        }
                                        else if (par->left == cur) {
                                                par->left = cur->left;
                                        }
                                        else {
                                                par->right = cur->left;
                                        }
                                }
                                else {
                                        cur->occurances--;
                                }
			}
			else if (!cur->left && cur->right) {
                                 if (cur->occurances == 1) {
                                        if (!par) {
                                                //cur is root
                                                root = cur->right;
                                        }
                                        else if (par->left == cur) {
                                                par->left = cur->right;
                                        }
                                        else {
                                                par->right = cur->right;
                                        }
                                }
                                else {
                                        cur->occurances--;
                                }
                        }
			else {
				//find successor
				Node* suc = cur->right;
				while (suc->left) {
					suc = suc->left;
				}
				
				string successorData = suc->data;
				remove(suc->data);
				cur->data = successorData;
			}
			return;
		}				
		else if (cur->data < key) {
			par = cur;
			cur = cur->right;
		}
		else {
			par = cur;
			cur = cur->left;
		}
	}
	return;
}

bool BSTree::search(const string& key) const {
	return search(key, root);
}

bool BSTree::search(const string& key, Node* node) const{
	if (!node)
		return false;
	if (node->data == key)
		return true;

	bool leftSide = search(key, node->left);

	if (leftSide)
		return true;

	bool rightSide = search(key, node->right);

	return rightSide;
}

Node* BSTree::returnNode(const string& key, Node* node) const{
        if (!node)
                return nullptr;

        if (node->data == key)
                return node;

        bool leftSide = search(key, node->left);

        if (leftSide)
                return returnNode(key, node->left);

        return returnNode(key, node->right);
}

string BSTree::largest() const {
	string largestString = "";
	return largest(largestString, root);
}

string BSTree::largest(const string& largestString, Node* node) const {

//	cout << "NODE DATA: " << node->data << endl;
	string newLargest;

	if (!node)
		return "";

	if (node->data > largestString)
		newLargest = node->data;
	else
		newLargest = largestString;

	if (node->left) {
//		cout << "node left exists" << endl;
		newLargest = largest(newLargest, node->left);
	}
	
	if (node->right) {
//		cout << "node right exists" << endl;
		newLargest = largest(newLargest, node->right);
	}

	return newLargest;
}

string BSTree::smallest() const {
	if (root) {
		string smallestString = root->data;
		return smallest(smallestString, root);
	}
	
	return "";
}

string BSTree::smallest(const string& smallestString, Node* node) const {
	string newSmallest;
//	cout << "NODE DATA: " << node->data << endl;

	if (!node)
		return "";

	if (node->data < smallestString)
		newSmallest = node->data;
	else
		newSmallest = smallestString;

	if (node->left) {
//		cout << "node left exists" << endl;
		newSmallest = smallest(newSmallest, node->left);
	}
	
	if (node->right) {
//		cout << "node right exists" << endl;
		newSmallest = smallest(newSmallest, node->right);
	}

	return newSmallest;
}

int BSTree::height(const string& key) const {
	if (search(key, root))
		return height(key, returnNode(key,root)) - 1;
	else
		return -1;
}

int BSTree::max(int left, int right) const {
	int val = right;

	if (left > right)
		val = left;
	return val;
}

int BSTree::height(const string& key, Node* node) const {
	if (!node)
		return 0;

	int left = height(key, node->left);
	int right = height(key, node->right);

	return 1 + max(left, right);
}

void BSTree::preOrder() const {
        preOrder(root);
}

void BSTree::preOrder(Node* node) const {
        if (node) {
                cout << node->data << "(" << node->occurances << ")" << ", ";
                preOrder(node->left);
                preOrder(node->right);
        }
}

void BSTree::inOrder() const {
        inOrder(root);
}

void BSTree::inOrder(Node* node) const {
        if (node) {
                inOrder(node->left);
                cout << node->data << "(" << node->occurances << ")" << ", ";
                inOrder(node->right);
        }
}

void BSTree::postOrder() const {
        postOrder(root);
}

void BSTree::postOrder(Node* node) const {
        if (node) {
                postOrder(node->left);
                postOrder(node->right);
                cout << node->data << "(" << node->occurances << ")" << ", ";
        }
}

