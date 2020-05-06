#include "arithmeticExpression.h"

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

arithmeticExpression::arithmeticExpression(const string& givenExpression) : infixExpression(givenExpression), root(nullptr) {}

arithmeticExpression::~arithmeticExpression() { 
	deleteNodes(root); 
	root = nullptr;
}

void arithmeticExpression::deleteNodes(TreeNode* node) {
	if (node) {
		deleteNodes(node->left);
		deleteNodes(node->right);

		delete node;		
        }
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;  
    }   
    else if(op == ')'){
        priority =  4;  
    }   
    else if(op == '*' || op == '/'){
        priority = 2;
    }   
    else if(op == '+' || op == '-'){
        priority = 1;
    }   
    return priority;
}

/*
string arithmeticExpression::buildPostfix() {
	string postfix;
        int priority = 0;
        stack<char> stack;
        stack.push('(');
        infixExpression.append(')');

        for (int i = 0; i < infixExpression.size(); i++) {
                priority(infixExpression.at(i));

                if (priority == 0) {
                        postfix.append(infixExpression.at(i));
                }   
                else if (priority == 1 || priority == 2) {
                        while (priority(stack.top()) >= priority) {
                                postfix.append(stack.pop());
                        }   

                        stack.push(infixExpression.at(i));
                }   
                else if (priority == 3) {
                        stack.push(infixExpression.at(i));
                }   
                else if (priority == 4) {
                        while (priority(stack.top()) != 3) {
                                postfix.append(stack.pop());
                        }   
                        stack.pop();
                }   
                else {
                        cout << "An Error Has Occured in BuildTree()" << endl;
        }  
	return postfix;
}
*/

TreeNode* arithmeticExpression::buildLeftChild(stack<char> stack,::stack<char> keyStack) {
	TreeNode* returnNode = nullptr;
	char key = keyStack.top();
	char stackKey = stack.top();

	if (priority(stack.top()) == 0) {
		stack.pop();
		keyStack.pop();
		returnNode = new TreeNode(stackKey, key);
	}	
	else {
		stack.pop();
                keyStack.pop();
                returnNode = new TreeNode(stackKey, key);
		returnNode->left = buildLeftChild(stack, keyStack);
		returnNode->right = buildRightChild(stack, keyStack);
	}
	
	return returnNode;
}

TreeNode* arithmeticExpression::buildRightChild(stack<char> stack, ::stack<char> keyStack) {
	TreeNode* returnNode = nullptr;
	char key = keyStack.top();
        char stackKey = stack.top();

        if (priority(stack.top()) == 0) {
		stack.pop();
                keyStack.pop();
                returnNode = new TreeNode(stackKey, key);
        }    
        else {
		stack.pop();
                keyStack.pop();
                returnNode = new TreeNode(stackKey, key);
                returnNode->left = buildLeftChild(stack, keyStack);
                returnNode->right = buildRightChild(stack, keyStack);
        }   
            
        return returnNode;
}

void arithmeticExpression::buildTree() {
	string postfix = infix_to_postfix();

	::stack<char> stack;
	::stack<char> keyStack;
	for (long unsigned int i = 0; i < postfix.size(); i++) {
		stack.push(postfix.at(i));
		keyStack.push(97 + i);
	}
	 char key = keyStack.top();
        char stackKey = stack.top();

	//tree is single node
	if (priority(stack.top()) == 0) {
		stack.pop();
                keyStack.pop();
                root = new TreeNode(stackKey, key);
	}
	else {
		stack.pop();
                keyStack.pop();
                root = new TreeNode(stackKey, key);
		root->left = buildLeftChild(stack, keyStack);
		root->right = buildRightChild(stack, keyStack);
	}
}

void arithmeticExpression::infix() { infix(root); }

void arithmeticExpression::infix(TreeNode* node) {
	if (node) {
		if (priority(node->data) == 2 || priority(node->data) == 1) {
			//if it is * or / or + or - put paranthesis
			cout << " (";
			infix(node->left);
			cout << ' ' << node->data;
			infix(node->right);
			cout << " )";
		}
		else
			cout << ' ' << node->data;
	}
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

void visualizeTree(ofstream &, TreeNode *) { }

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::prefix(TreeNode *node) {
    cout << node->key;
    if (node->left != nullptr) {
        postfix(node->left);
    } 
    if (node->right != nullptr) {
        postfix(node->right);
    }
}

void arithmeticExpression::postfix(TreeNode *node) {
    if (node->left != nullptr) {
        postfix(node->left);
    } 
    if (node->right != nullptr) {
        postfix(node->right);
    } 
    cout << node->key;
}
