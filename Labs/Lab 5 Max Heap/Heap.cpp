#include "Heap.h"

#include <iostream>

using namespace std;

Heap::Heap() : numItems(0) {}

void Heap::enqueue(PrintJob* job) {
	int currentElementIndex = 0;

	if (numItems != MAX_HEAP_SIZE) {
		if (numItems == 0) {
			arr[0] = job;
			numItems++;
		}
		else {
			arr[numItems] = job;
			numItems++;
			
			currentElementIndex = numItems - 1;
			while (currentElementIndex > 0) {
				int parentIndex = (currentElementIndex - 1) / 2;

				if (arr[currentElementIndex]->getPriority() <= arr[parentIndex]->getPriority())
					return;
				else {
					PrintJob* temp = arr[parentIndex];
					arr[parentIndex] = arr[currentElementIndex];
					arr[currentElementIndex] = temp;
					currentElementIndex = parentIndex;
				}
			}
		}
	}
}

void Heap::dequeue() {
	if (numItems == 0) 
		cout << "Tried to dequeue with no items in the heap" << endl;
	else if (numItems == 1) {
		numItems--;
		return;
	}
	else {
		arr[0] = arr[numItems - 1];
		numItems--;
		trickleDown(0);
	}

}

PrintJob* Heap::highest() { 
	if (numItems != 0)
		return arr[0]; 
	return nullptr;
}

void Heap::print() {
	PrintJob* job = highest();
	if (job == nullptr)
		cout << "Empty Heap" << endl;
	else 
		cout << "Priority: " << job->getPriority() << ", Job Number: " << job->getJobNumber() << ", Number of Pages: " << job->getPages() << endl;
}

void Heap::trickleDown(int nodeIndex) {
	int childIndex = (2 * nodeIndex) + 1;
	int priority = arr[nodeIndex]->getPriority();

	while (childIndex < numItems) {
		int maxPriority = priority;
		int maxIndex = -1;

		for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
			if (arr[i + childIndex]->getPriority() > maxPriority) {
				maxPriority = arr[i + childIndex]->getPriority();
				maxIndex = i + childIndex;
			}
		}
//		maxIndex = maxIndex;
		if (maxPriority == priority) {
			return;
		}
		else {
			PrintJob* temp = arr[nodeIndex];
			arr[nodeIndex] = arr[maxIndex];
			arr[maxIndex] = temp;
			nodeIndex = maxIndex;
			childIndex = 2 * nodeIndex + 1;
		}
	}
}
