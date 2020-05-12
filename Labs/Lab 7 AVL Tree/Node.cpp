#include "Node.h"

#include <iostream>

using namespace std;

Node::Node(const string &input) : data(input) {
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}
