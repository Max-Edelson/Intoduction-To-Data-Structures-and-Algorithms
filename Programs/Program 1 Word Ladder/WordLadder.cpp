//Made by Maxim Edelson and Chris Young

#include "WordLadder.h"

using namespace std;

WordLadder::WordLadder(const string &fileName) {

	ifstream inFS;
	string currWord;

	inFS.open(fileName);

	//make sure the file opened correctly
	if (!inFS.is_open()) {
		cout << "Error. File could not open." << endl;
		return;
	}

	//loop loads up the list with the dictionary
	while (inFS >> currWord && !inFS.bad()) {

		//checks if the word length is 5 letters long. 1 char == 1 byte
		if (currWord.size() != 5) {
			cout << "Error. Word exists that is not 5 letters." << endl;
			return;
		}
		dict.push_back(currWord);
	}
	
	inFS.close();
}
