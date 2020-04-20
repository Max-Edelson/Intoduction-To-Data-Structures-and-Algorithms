#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

using namespace std;

static const int MAX_SIZE = 20; 

template<typename T>
class stack {

        private: 
                int size;
                T data[MAX_SIZE];

        public:
                stack();
                void push(T val);
                void pop();
                T top();
                bool empty();
};

template<typename T>
stack<T>::stack() {}

template<typename T>
void stack<T>::push(T val) {
        if (size == MAX_SIZE) {
                throw overflow_error("Called push on full stack.");
        }   

	size++;
        data[size - 1] = val;
}

template<typename T>
void stack<T>::pop() {
        if (size == 0) {
                throw out_of_range("Called pop on empty stack.");
        }   

        size--;
}

template<typename T>
T stack<T>::top() {
        T returnVal;

        if (size == 0) {
                throw underflow_error("Called top on empty stack.");
        }   
                     
        returnVal = data[this->size - 1]; 

        return returnVal;
}

template<typename T>
bool stack<T>::empty() {
        bool returnVal = true;
            
        if (size > 0) {
                returnVal = false;
        }

        return returnVal;
}

#endif
