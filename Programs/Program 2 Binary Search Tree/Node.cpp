#include "Node.h"

#include <iostream>

using namespace std;

Node::Node(string inputString) : data(inputString), occurances(1), left(nullptr), right(nullptr) {}
