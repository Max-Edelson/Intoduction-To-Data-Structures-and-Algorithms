#include "BSTree.h"

#include <iostream>

using namespace std;

BSTree::BSTree() : root(nullptr) {}

BSTree::~BSTree() {
	deleteNodes(root);
	root = nullptr;
}

BSTree::deleteNodes(Node* node) {
	if (node) {
		deleteNodes(node->left);
		deleteNodes(node->right);
		delete node;
	}
}

void BSTree::insert(const string &newString) {

	if (!temp) {
		root = new Node(newString);
	}
	else {
		Node* temp = root;

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
				if (curr->occurances == 1) {
					if (!par) {
						//cur is root
						delete cur;
						root = nullptr;
					}
					else if (par->left == cur) {
						par->left == nullptr;
					}
					else {
						par->right = nullptr;
					}
				}
				else {
					curr->occurances--;
				}
			}
			else if (cur->left && !cur->right) {
				 if (curr->occurances == 1) {
                                        if (!par) {
                                                //cur is root
                                                root = cur->left;
                                        }
                                        else if (par->left == cur) {
                                                par->left == cur->left;
                                        }
                                        else {
                                                par->right = cur->left;
                                        }
                                }
                                else {
                                        curr->occurances--;
                                }
			}
			else if (!cur->left && cur->right) {
                                 if (curr->occurances == 1) {
                                        if (!par) {
                                                //cur is root
                                                root = cur->right;
                                        }
                                        else if (par->left == cur) {
                                                par->left == cur->right;
                                        }
                                        else {
                                                par->right = cur->right;
                                        }
                                }
                                else {
                                        curr->occurances--;
                                }
                        }
			else {
				//find successor
				Node* suc = cur->right;
				while (suc->left) {
					suc = suc->left;
				}
				
				string successorData = suc->data;
				BSTRemove(suc->data);
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













