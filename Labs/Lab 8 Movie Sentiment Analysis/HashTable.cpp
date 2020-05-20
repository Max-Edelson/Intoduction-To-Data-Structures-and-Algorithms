#include "HashTable.h"
#include "WordEntry.h"

#include <iostream>
#include <list>
#include <string>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include <math.h>

using namespace std;


/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	hashTable = new list<WordEntry> [s];
	size = s;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
	int hashVal = 0;

	for (unsigned i = 0; i < s.size() && i < 3; i++) {
		for (unsigned j = 0; j < i; j++) {
			hashVal += s.at(i) * pow(32, j);
		}
	}

	return hashVal % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
	int index = 0; 

	index = computeHash(s);
	bool found = false;

	list<WordEntry>::iterator it;

	for (it = hashTable[index].begin(); it !=hashTable[index].end(); it++) {
		if (it->getWord() == s) {
			it->addNewAppearance(score);
			found = true;
		}
	}
	
	if (!found) {
		hashTable[index].push_back(WordEntry(s, score));	
	}

}

void HashTable::dumpHashTable() const {
	int bucket = 0;
	list<WordEntry>::iterator it;

	for (int i = 0; i < size; i++) {
		cout << "Bucket " << bucket << ", List: ";

		for (it = hashTable[i].begin(); it !=hashTable[i].end(); it++) {
			cout << it->getWord() << "(" << it->getAppearances() << ", " << it->getScore() << ")";
			
		}
		cout << endl;
	}
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
	int index = 0;

        index = computeHash(s);

	double returnVal = 2.0;
        
	list<WordEntry>::iterator it;
        
        for (it = hashTable[index].begin(); it !=hashTable[index].end(); it++) {
                if (it->getWord() == s) {
			returnVal = it->getAverage();
                }       
        }

	return returnVal;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
	int index = 0;
        
        index = computeHash(s);
        bool found = false;
        
	list<WordEntry>::iterator it;
        
        for (it = hashTable[index].begin(); it !=hashTable[index].end(); it++) {
                if (it->getWord() == s) {
                        found = true;
                }       
        }
        
	return found;
}

