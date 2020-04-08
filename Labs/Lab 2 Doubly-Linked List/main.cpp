#include "IntList.h"

#include <iostream>

using namespace std;

int main() {

	IntList list;
/*
	cout << "push front 179" << endl;
	list.push_front(179);
	cout << list << endl;

	cout << "push front 45" << endl;
	list.push_front(45);
	cout << list << endl;
*/
	list.push_back(138);
	cout << list << endl;

	list.push_back(98);
	cout << list << endl;

	list.push_back(66);
 	cout << list << endl;

	list.push_back(168);
	cout << list << endl;
	
	list.push_back(107);
	cout << list << endl;
	
	list.push_back(121);
	cout << list << endl;

	list.push_back(-74);
	cout << list << endl;

	list.push_back(49);
	cout << list << endl;

	list.push_back(188);
	cout << list << endl;

	cout << "print in reverse" << endl;
	list.printReverse();
/*
	cout << "pop_back" << endl;
	list.pop_back();
	cout << list;

	cout << "pop_front" << endl;
	list.pop_front();
	cout << list;

	cout << "testing empty: " << list.empty() << endl;

	cout << "pop_back" << endl;
	list.pop_back();

	cout << "pop_front" << endl;
	list.pop_front();

	cout << "testing empty: " << list.empty() << endl;
*/
	return 0;
}
