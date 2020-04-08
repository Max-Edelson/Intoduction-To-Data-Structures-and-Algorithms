#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

struct Node {

	string name;
	Node* next;
	Node* prev;
	Node(string name) : name(name), next(nullptr), prev(nullptr) {}
};

class List {

	private:
		Node* head;
		Node* tail;
		int size;

	public:
		List() : head(nullptr), tail(nullptr), size(0) {}
		~List();
		void print();
		void addNewPerson(string person);
		void removePerson(Node* person);
		string execute(int, int personToStartFromName);		

};

#endif
