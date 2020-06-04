#include <iostream>

using namespace std;

enum Action { fillA, fillB, emptyA, emptyB, pourAB, pourBA, invalid };

struct Vertex {
	int fillA;
	int fillB;
	Action action;
	string history;
	int cost;
	Vertex() {}
};


class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();
        
        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string. 
        int solve(string &solution);
        void buildGraph();
    private:
	Action graph[100][100];
	const string actionString(enum Action);
	int index(int, int);
	int determineCost(enum Action);
	int capA;
	int capB;
	int goal;
	int cfA;
	int cfB;
	int ceA;
	int ceB;
	int cpAB;
	int cpBA;
        //anything else you need
};
