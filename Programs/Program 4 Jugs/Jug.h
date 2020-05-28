#include <iostream>
#include <string>

using namespace std;

enum action {fillA,fillB,emptyA,emptyB,pourAB,pourBA};

struct node {

        private:
                int totalCost;
                int fullnessA;
                int fullnessB;
		int cost;

        public:
		string answer;	
                action Action;
		
                node(action type, int stateA, int stateB, int actionCost, int c, string a) : totalCost(c), fullnessA(stateA), fullnessB(stateB), cost(actionCost), answer(a) {
			Action = type;
			string str = to_string(type);
			totalCost += cost;
			answer.append(str);
		}

                action getType() const { return Action; }
                int getTotal() const { return totalCost; }
                void addToTotal(int a) { totalCost += a; }
		int getA() { return fullnessA; }
		int getB() { return fullnessB; }

};

class Jug {

	private:
		int capacityA;
		int capacityB;
		int goal;
		int costFillA;
		int costFillB;
		int costEmptyA;
		int costEmptyB;
		int costPourA;
		int costPourB;

	public:
		Jug(int, int, int, int, int, int, int, int, int);
		~Jug();
		int solve(string &);
};
