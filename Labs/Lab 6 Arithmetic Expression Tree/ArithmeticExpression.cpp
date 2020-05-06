#include "ArithmeticExpression.h"

#include <iostream>
#include <stack>
#include <vector>

arithmeticExpression::arithmeticExpression(const string& givenExpression) : infixExpression(givenExpression), root(nullptr) {}

arithmeticExpression::~arithmeticExpression() { 
	deleteNodes(root); 
	root = null;
}

void arithmeticExpression::deleteNodes(TreeNode* node) {
	if (root) {
		deleteNodes(node->left);
		deleteNodes(node->right);

		delete node;		
        }
}

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

TreeNode* buildLeftChild(stack<char> stack, stack<char> keyStack) {
	TreeNode* returnNode == nullptr;

	if (priority(stack.top()) == 0) {
		returnNode = new TreeNode(stack.pop(),keyStack.pop());
	}	
	else {
		returnNode = new TreeNode(stack.pop(),keyStack.pop());
		returnNode->left = buildLeftChild(stack, keyStack);
		returnNode->right = buildRightChild(stack, keyStack);
	}
	
	return returnNode;
}

TreeNode* buildRightChild(stack<char> stack, stack<char> keyStack) {
	TreeNode* returnNode == nullptr;

        if (priority(stack.top()) == 0) {
                returnNode = new TreeNode(stack.pop(),keyStack.pop());
        }    
        else {
                returnNode = new TreeNode(stack.pop(),keyStack.pop());
                returnNode->left = buildLeftChild(stack, keyStack);
                returnNode->right = buildRightChild(stack, keyStack);
        }   
            
        return returnNode;
}

void arithmeticExpression::buildTree() {
	string postfix = buildPostfix();

	stack<char> stack;
	stack<char> keyStack;
	for (int i = 0; i < postfix.size(); i++) {
		stack.push(postfix.at(i));
		keyStack.push(97 + i);
	}

	//tree is single node
	if (priority(stack.top()) == 0) {
		root = new TreeNode(stack.pop(), keyStack.pop());
	}
	else {
		root = new TreeNode(stack.pop(), keyStack.pop());
		root->leftChild = buildLeftChild(stack);
		root->rightChild = buildRightChild(stack);
	}
}

void arithmeticExpression::infix() { infix(root); }

void arithmeticExpression::infix(TreeNode* node) {
	if (node) {
		if (priority(node->data) == 2 || priority(node->data) == 1) {
			//if it is * or / or + or - put paranthesis
			cout << ' (';
			infix(node->left);
			cout << ' ' << node->data;
			infix(node->right);
			cout << ' )';
		}
		else
			cout << ' ' << node->data;
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
main.cpp test harness

Use this main.cpp file for testing your program.

#include <iostream>
#include "arithmeticExpression.h"

using namespace std;

int main(){
    string expr1 = "a+b*c";
    arithmeticExpression ex1(expr1);
    ex1.buildTree();
    cout<<"expression 1: "<<expr1<<endl;
    cout<<"infix: "; ex1.infix(); cout<<endl;
    cout<<"prefix: "; ex1.prefix(); cout<<endl;
    cout<<"postfix: "; ex1.postfix(); cout<<endl;
    //ex1.visualizeTree("expr1.dot");
    cout<<endl;

    string expr2 = "(a+b)*(c-d)";
    arithmeticExpression ex2(expr2);
    ex2.buildTree();
    cout<<"expression 2: "<<expr2<<endl;
    cout<<"infix: "; ex2.infix(); cout<<endl;
    cout<<"prefix: "; ex2.prefix(); cout<<endl;
    cout<<"postfix: "; ex2.postfix(); cout<<endl;
    //ex2.visualizeTree("expr2.dot");
    cout<<endl;

    string expr3 = "a + b * c - ( d * e + f ) * g";
    arithmeticExpression ex3(expr3);
    ex3.buildTree();
    cout<<"expression 3: "<<expr3<<endl;
    cout<<"infix: "; ex3.infix(); cout<<endl;
    cout<<"prefix: "; ex3.prefix(); cout<<endl;
    cout<<"postfix: "; ex3.postfix(); cout<<endl;
    //ex3.visualizeTree("expr3.dot");
    cout<<endl;

    return 0;
}
