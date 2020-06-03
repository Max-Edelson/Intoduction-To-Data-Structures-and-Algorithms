#include "Jug.h"

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) : capacityA(Ca), capacityB(Cb), goal(N), costFillA(cfA), costFillB(cfB), costEmptyA(ceA), costEmptyB(ceB), costPourA(cpAB), costPourB(cpBA) {}

Jug::~Jug() {}

int Jug::solve(string &solution) {

	if (capacityA <= 0 || capacityB <= 0 || capacityA > capacityB) {
		solution = "";
                return -1;
	}
        if (goal > capacityB || goal > 1000 || capacityB > 1000) {
		solution = "";
                return -1; 
	}
        if (costFillA <= 0 || costFillB <= 0 || costEmptyA <= 0 || costEmptyB <= 0 || costPourA <= 0 || costPourB <= 0) {
		solution = "";
                return -1;
	}

	queue<node *> queue;
	
	node *temp = new node(fillA,0,0,costFillA,0,"");
	queue.push(temp);

	temp = new node(fillB,0,0,costFillB,0,"");
        queue.push(temp);

	temp = new node(emptyA,0,0,costEmptyA,0,"");
        queue.push(temp);

	temp = new node(emptyB,0,0,costEmptyB,0,"");
        queue.push(temp);

	temp = new node(pourAB,0,0,costPourA,0,"");
        queue.push(temp);
	
	temp = new node(pourBA,0,0,costPourB,0,"");
        queue.push(temp);

	while (!queue.empty()) {
		node *curr = queue.front();
		queue.pop();
		
		if (curr->getA() == 0 && curr->getB() == goal) {
			//done
			for (unsigned i = 0; i < curr->answer.size(); i++) {

				char character = curr->answer.at(i);			
				if (character == '0')
					cout << "fill A" << endl;

				else if (character == '1')
					cout << "fill B" << endl;

				else if (character == '2')
					cout << "empty A" << endl;

				else if (character == '3')
					cout << "empty B" << endl;

				else if (character == '4')
					cout << "pour A B" << endl;

				else if (character == '5')
					cout << "pour B A" << endl;
		
				else 
					cout << "mhmmm thats wrong" << endl;

			}
			cout << "success " << curr->getTotal();
			return 1;
		}	

		for (int i = 0; i < 6; i++) {
			if (i != curr->Action) {
/*				if (i == 0 && curr->getA() == capacityA) 
					//invalid
					;
				else if (i == 1 && curr->getB() == capacityB)
					//invalid
					;
				else if (i == 2 && curr->getA() == 0)
					// invalid
					;
				else if (i == 3 && curr->getB() == 0)
					//invalid
					;
				else if ((i == 4 && curr->getA() == 0) || (i == 4 && curr->getB() == capacityB))
					//invalid
					;
				else if ((i == 5 && curr->getA() == capacityB) || (i == 5 && curr->getB() == 0))
					//invalid
					;
*/
				node *newNode;
				
				switch (i) {
					case (0):
						newNode = new node(fillA, capacityA, curr->getB(), costFillA, curr->getTotal(), curr->answer);
						queue.push(newNode);
						break;
					case (1):
						newNode = new node(fillB, curr->getA(), capacityB, costFillB, curr->getTotal(), curr->answer);
						queue.push(newNode);
						break;
					case (2):
						newNode = new node(emptyA, 0, curr->getB(), costEmptyA, curr->getTotal(), curr->answer);
						queue.push(newNode);
						break;
					case (3):
						newNode = new node(emptyB, curr->getA(), 0, costEmptyB, curr->getTotal(), curr->answer);
						queue.push(newNode);
						break;
					case (4):
						if (curr->getB() + curr->getA() <= capacityB) {
							newNode = new node(pourAB, 0, curr->getB() + curr->getA(), costPourA, curr->getTotal(), curr->answer);
						}
						else {
							int difference = capacityB - curr->getB();
							newNode = new node(pourAB, curr->getA() - difference, curr->getB() + difference, costPourA, curr->getTotal(), curr->answer);
						}
						queue.push(newNode);
						break;
					case (5):
						if (curr->getB() + curr->getA() <= capacityA) {
							newNode = new node(pourBA, curr->getA() + curr->getB(), 0, costPourB, curr->getTotal(), curr->answer);
						}
						else {
							int difference = capacityA - curr->getA();
							newNode = new node(pourBA, curr->getA() + difference, curr->getB() - difference, costPourB, curr->getTotal(), curr->answer);
						}
						queue.push(newNode);
						break;
					default:
						cout << "someone broke math" << endl;
						break;
				} 
			}	
		}
	}
	return 0;
}














