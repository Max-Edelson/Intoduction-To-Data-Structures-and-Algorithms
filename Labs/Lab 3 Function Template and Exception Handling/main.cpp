//Collaborated with Chris Young

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template <typename T>
T getElement(vector<T> vals, int index) {	
	return vals.at(index);
}

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
	int min = index;

	for (unsigned i = index; i < vals.size(); i++) {
		if (vals.at(i) < vals.at(min))
			min = i;
	}

	return min;
}

template <typename T>
 void printVector(vector<T> &vals) {
         
         for (unsigned i = 0; i < vals.size(); i++) { 
                 cout << "vals[i]: " << vals.at(i) << endl;
         }
}

template <typename T>
void selection_sort(vector<T> &vals) {
	
	for (unsigned i = 0; i < vals.size(); i++) {
		int minIndex = min_index(vals, i);

		if (minIndex >= 0) {

			T temp = vals.at(i);
			vals.at(i) = vals.at(minIndex);
			vals.at(minIndex) = temp;
		}
	}

}

int main() {

	//Part A
	vector<int> vec;
	vec.push_back(-6);
	vec.push_back(-19);
	
	selection_sort(vec);

/*
	//Part B
	srand(time(0));
	vector<char> vals = createVector();
	char curChar;
	unsigned int index;
	int numOfRuns = 10;

	while(--numOfRuns >= 0){
		 cout << "Enter a number: " << endl;
		 cin >> index;

		 try {
			if (index >= vals.size() || vals.size() == 0)
				 throw runtime_error("std::out_of_range.");
							
			curChar = getElement(vals,index);
			cout << "Element located at " << index << ": is " << curChar << endl;
		 }
		 catch(const std::out_of_range& excpt) {
			 cout << "out of range exception occured" << endl;
		 }
	}
*/
	return 0;
}
