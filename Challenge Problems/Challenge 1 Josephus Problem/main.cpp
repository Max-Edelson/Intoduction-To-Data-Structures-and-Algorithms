#include "List.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

	vector<string> people;
	string currentPerson;

	ifstream inFS;
	inFS.open("people.txt");

	if (!inFS.is_open()) {
		cout << "Error openning the file" << endl;
		return 1;
	}	
	else {
		while (getline(inFS,currentPerson) && !inFS.eof()) {
			people.push_back(currentPerson);
		}
	}

	inFS.close();

	int numPeople = 0;
	int numPeopleToSkip = 0;
	int unluckyWinner = 0;

	cout << "Total Number of People (must be less than 10): ";
	cin >> numPeople;

	cout << "Number of people to skip between executions: ";
	cin >> numPeopleToSkip;

	cout << "Number of person to start from (must be less than total number of people (0,n-1)): ";
	cin >> unluckyWinner;

	int counter = 0;

	List personList;

	while (counter < numPeople) {
		personList.addNewPerson(people.at(counter));
		counter++;
	}	

	cout << personList.execute(numPeopleToSkip, unluckyWinner) << " survived" << endl;

	//~personList();

	return 0;
}
