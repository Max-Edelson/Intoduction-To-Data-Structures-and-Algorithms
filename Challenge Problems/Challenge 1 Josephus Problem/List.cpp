#include "List.h"

#include <iostream>

using namespace std;

List::~List() {
	delete head;
	head = nullptr;
	tail = nullptr;
}

void List::addNewPerson(string person) {
	Node* newPerson = new Node(person);
	size++;

	if (!head) {
		head = newPerson;
		tail = newPerson;
		head->next = head;
		head->prev = head;
		tail->next = head;
		tail->prev = head;
	}
	else {
		tail->next = newPerson;
		newPerson->next = head;
		newPerson->prev = tail;
		tail = newPerson;
	}
}

void List::removePerson(Node* person) {

	Node* temp = person;

	temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

	if (temp == head) {
		head = temp->next;
	}
	else if (temp == tail) {
		tail = temp->prev;
	}
	
	delete temp;	
}

void List::print() {
	Node* temp = head;
	int counter = 0;

	while (temp && counter < 2) {
		if (temp == head)
			counter++;
	
		if (counter < 2) {
			cout << temp->name << endl;
			temp = temp->next;
		}
	}
}

string List::execute(int numberToSkipBy, int personToStartFromNumber) {
	int personCounter = 0;
	int traversionCounter = 0;

	if (!head) {
		return "none";
	}	

	Node* personToStartFrom = head;	

	while (personCounter != personToStartFromNumber && traversionCounter < 2) {
		if (personToStartFrom == head) {
			traversionCounter++;
		}	

		personToStartFrom = personToStartFrom->next;
		personCounter++;
	}

	if (traversionCounter == 2)
		return "there isn't a person with that name in the circle of death";

	Node* currentPerson = personToStartFrom;

	while (size > 1) {
		//print();
		for (int i = 0; i <= numberToSkipBy; i++) {
			currentPerson = currentPerson->next;
		} 
		removePerson(currentPerson);
		size--;
	}
	
	return head->name;
}
