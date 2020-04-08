#include "IntList.h"

#include <iostream>
#include <string>
#include <limits>
#include <climits>

using namespace std;

IntList::IntList() {
	IntNode* head = new IntNode(INT_MAX);
	IntNode* tail = new IntNode(INT_MAX);

	head->next = tail;
	head->prev = tail;;
	
	tail->next = head;
	tail->prev = head;

	dummyHead = head;
	dummyTail = tail;
}

IntList::~IntList() {
	IntNode* temp = dummyHead;

	while (temp != dummyTail) {
		if (temp->data != INT_MAX) {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			
			delete temp;
		}
		temp = temp->next;
	}
}

void IntList::push_front(int value) {
	IntNode* temp = new IntNode(value);

	temp->next = dummyHead->next;
	temp->prev = dummyHead;

	dummyHead->next->prev = temp;
	dummyHead->next = temp;
}

void IntList::pop_front() {
	if (dummyHead->next->data != INT_MAX) {
		IntNode* temp = dummyHead->next;

		dummyHead->next = temp->next;
		temp->next->prev = dummyHead;

		delete temp;
	}
}

void IntList::push_back(int value) {
	IntNode* temp = new IntNode(value);

	temp->prev = dummyTail->prev;
	temp->next = dummyTail;

	dummyTail->prev->next = temp;
	dummyTail->prev = temp;
}

void IntList::pop_back() {
	if (dummyTail->prev->data != INT_MAX) {
		IntNode* temp = dummyTail->prev;

		temp->prev->next = dummyTail;
		dummyTail->prev = temp->prev;

		delete temp;		
	}
}

bool IntList::empty() const {
	if (dummyHead->next->data != INT_MAX)
		return false;
	return true;
}

ostream& operator<<(ostream &out, const IntList &rhs) {
	IntNode* temp = rhs.dummyHead->next;

	while (temp->data != INT_MAX) {
		if (rhs.dummyHead->next == temp)
			out << temp->data;
		else 
			out << " " << temp->data;

		temp = temp->next;
	}

	return out;
}

void IntList::printReverse() const {
	IntNode* temp = dummyTail->prev;
	string out = "";	


	while (temp != dummyHead) {
		string data = "";

		if (temp->prev == dummyHead) {
			data = to_string(temp->data);
		}
		else {
			data.append(to_string(temp->data));
			data.append(" ");
		}

/*		cout << "temp->data: " << temp->data << endl;
		cout << "data: " << data << endl;
*/
		out.append(data);

		temp = temp->prev;
	}
	cout << out;
}
