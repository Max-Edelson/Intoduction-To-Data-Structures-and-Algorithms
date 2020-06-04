#include "Jug.h"

#include <iostream>
#include <queue>
#include <assert.h>

using namespace std;

int min(int a, int b) {
	int result = a;
	if (b > a)
		result = b;
	return result;
}

const string Jug::actionString(enum Action a) {
	switch (a) {
		case fillA: return "fillA";
		case fillB: return "fillB";	
		case emptyA: return "emptyA";
		case emptyB: return "emptyB";
		case pourAB: return "pourAB";
		case pourBA: return "pourBA";
		default:
			assert(0);
	}
}

int MAX_CAP = 100;

Jug::Jug(int cA, int cB, int n, int c1, int c2, int c3, int c4, int c5, int c6) : capA(cA), capB(cB), goal(n), cfA(c1), cfB(c2), ceA(c3), ceB(c4), cpAB(c5), cpBA(c6) {

	//set the state for all possible verticies to invalid
	for (int i = 0; i < capA; i++) {
		for (int j = 0; j < capA; j++) {
			for (int i2 = 0; i2 < capA; i2++) {
				for (int j2 = 0; j2 < capB; j++) {
					graph[index(i,j)][index(i2,j2)] = invalid;
				}
			}
		}
	}

	//for all starting states, determine 6 possible actions and update the graph
	for (int i = 0; i < capA; i++) {
		for (int j = 0; j < capB; j++) {
			Action action;
			int fullnessA;
			int fullnessB;
			int pourAmount;
			int x;
			int y;

			// x is our current state
			// y is the state that we will be going to
			x = index(i, j);

			//fill a
			action = fillA;
			fullnessA = capA;
			fullnessB = j;
			y = index(fullnessA, fullnessB);
			graph[x][y] = action;

			//fill b
			action = fillB;
			fullnessA = i;
			fullnessB = capB;
			y = index(fullnessA, fullnessB);
                        graph[x][y] = action;

			//empty a
			action = emptyA;
			fullnessA = 0;
			fullnessB = j;
			y = index(fullnessA, fullnessB);
                        graph[x][y] = action;

			//empty b
			action = emptyB;
			fullnessA = i;
			fullnessB = 0;
			y = index(fullnessA, fullnessB);
                        graph[x][y] = action;

			//pour AB
			action = pourAB;
			fullnessA = i;
			fullnessB = j;
			pourAmount = min(fullnessA, capB - fullnessB);
			fullnessA -= pourAmount;
			fullnessB += pourAmount;
			y = index(fullnessA, fullnessB);
                        graph[x][y] = action;

			//pour BA
			action = pourBA;
			fullnessA = i;
			fullnessB = j;
			pourAmount = min(capA - fullnessA, fullnessB);
			fullnessA += pourAmount;
			fullnessB -= pourAmount;
			y = index(fullnessA, fullnessB);
                        graph[x][y] = action;
		}
	}

	for (int i = 0; i < capA; i++) {
		for (int j = 0; j < capB; j++) {
			graph[index(i, j)][index(i, j)] = invalid;
		}
	}
}

int Jug::index(int fillA, int fillB) {
	return (fillA * (capA + 1)) + fillB;
}

int Jug::determineCost(enum Action action) {
	switch (action) {
		case fillA: return cfA;
		case fillB: return cfB;
		case emptyA: return ceA;
		case emptyB: return ceB;
		case pourAB: return pourAB;
		case pourBA: return pourBA;
		default: 
			assert(0);
	}
}

int Jug::solve(string &solution) {
	if (capA > capB || capB <= 0 || capA <= 0 || goal >= 1000 || goal > capB || capB > 1000)
		return -1;
		
	int solved = false;
	bool visited[MAX_CAP];
	vector<Vertex *> vector;

	//create an initial edge for the initial state
	Vertex* ptr = new Vertex;
	ptr->fillA = 0;
	ptr->fillB = 0;
	ptr->action = invalid;
	ptr->history = "";
	ptr->cost = 0;
	vector.push_back(ptr);

	for (int i = 0; i < MAX_CAP; i++)
		visited[i] = false;

	//BFS
	while (vector.size() > 0) {
		int min = 0;
		for (unsigned k = 0; k < vector.size(); k++) {
			if (vector.at(k)->cost < vector.at(min)->cost)
				min = k;
		}
		Vertex *ptr = vector.at(min);
		vector.erase(vector.begin() + min);

		assert(ptr != nullptr);
		int x = index(ptr->fillA, ptr->fillB);
		if (visited[x])
			//duplicate
			;
		else {
			visited[x] = true;
			if (ptr->fillA == 0 && ptr->fillB == goal) {
				solved = true;
				string hist = "\nSuccess " + to_string(ptr->cost);
				ptr->history += hist;
				solution = ptr->history;
			}
			else {
				//enqueue all possible nodes
				for (unsigned i = 0 ; i < capA; i++) {
					for (unsigned j = 0; j < capB; j++) {
						int y = index(i,j);
						Action a = graph[x][y];
						if (a != invalid) {
							Vertex* curr = new Vertex;
							curr->fillA = i;
							curr->fillB = j;
							curr->action = a;
							curr->cost = ptr->cost + determineCost(a);
							string s = ptr->history;
							s += "\n" + actionString(a);
							curr->history = s;
							vector.push_back(curr);
						}
					}
				}
			}
		}
		delete ptr;
		ptr = nullptr;
	}
	if (!solved)
		return 0;
	else
		return 1;
}
