#include <iostream>
#include "Playlist.h"

using namespace std;

Playlist::~Playlist() {
	while(head) {
		PlaylistNode* temp = head->GetNext();
		delete head;
		head = temp;
	}
	tail = nullptr;
}

void Playlist::AddSong(string ID, string sName, string aName, int length) {
	
	PlaylistNode* temp = new PlaylistNode(ID, sName, aName, length, nullptr);

	if (!head) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = temp;
	}
}

string Playlist::RemoveSong(string ID) {
	if (!head) {}
	else {
		PlaylistNode* curr = head->next;
		PlaylistNode* prev = head;
		
		if (head->GetID() == ID) {
			string name = head->GetSongName();
			delete head;
			head->next = nullptr;
			return name;
		}
		else {
			while (curr) {
				if (curr->GetID() == ID) {
					string name = curr->GetSongName();
					prev->next = curr->next;
					delete curr;
					
					if (prev->next == nullptr)
						prev = tail;
					
					return name;
				}
				curr = curr->next;
				prev = prev->next;
			}
		}
	}
	return "No song of that ID";
}

string Playlist::ChangePosition(int currPosition, int desired) {
	string returnSongName;
	
	if (currPosition == desired) {
		if (currPosition == 1)
			return head->GetSongName();
		else {
			int count = 1;
			PlaylistNode* pntr = head;
			while (pntr) {
				if (count == currPosition)
					break;
				pntr = pntr->next;
				count++;
			}
			return pntr->GetSongName();
		}
	}		
	
	if (head) {

		if (currPosition == 1) {
			int counter = 1;
			PlaylistNode* insertionLocation = head->next;
			PlaylistNode* beforeInsertionLocation = head;

			while (insertionLocation) {
				if (counter == desired)
					break;
				
				insertionLocation = insertionLocation->next;
				beforeInsertionLocation = beforeInsertionLocation->next;
				counter++;
			}

			 PlaylistNode* temp = head;

			if (counter < desired) {
				head = temp->next;
				temp->next = nullptr;
				tail->next = temp;	
			}
			else if (counter > desired) {
				//send node to the front
				//do nothin
			}
			else {
				head = temp->next;
				temp->next = insertionLocation;
				beforeInsertionLocation->next = temp;
			}
                        returnSongName = temp->GetSongName();
                }	
		else {		

			PlaylistNode* temp = head->next;
			PlaylistNode* previous = head;
			int positionCounter = 2;
			
			//finds the node corresponding the the node in question
			while (temp) {
				if (positionCounter == currPosition)
					break;
				positionCounter++;                 					//this might need to be incremented once more;
				temp = temp->next;
				previous = previous->next;
			}

			//finds the total number of nodes
			PlaylistNode* counterPntr = head;
			int listCounter = 0;
			while (counterPntr) {
				listCounter++;
				counterPntr = counterPntr->next;
			}

			if (!head) { returnSongName = "Playlist is empty"; }
			else if (desired <= 1) {
	                        previous->next = temp->next;
                	        temp->next = head;
        	                head = temp;
	                        returnSongName = temp->GetSongName();
                	}
			/*else if (desired == listCounter) {
				PlaylistNode* curr = head;
				while (curr->next->next != nullptr) {
					curr = curr->next;
				}

				previous->next = temp->next;

				curr->next = temp;
				temp->next = tail;
				returnSongName = temp->GetSongName();
			}*/
			else if (desired >= listCounter) {
				if (temp == tail) {}
				else {
					previous->next = temp->next;

					tail->next = temp;
					tail = temp;
					tail->next = nullptr;
				}
				returnSongName = temp->GetSongName();
				cout << "change 3" << endl;
			}
			else {

					previous->next = temp->next;
					temp->next = nullptr;

					PlaylistNode* prev = head;
                                        for (int i = 1; i < desired - 1; i++) {
                                                prev = prev->next;
                                        }

					temp->next = prev->next;
                                        prev->next = temp;
				returnSongName = temp->GetSongName();
			}	
		}
	}	
	return returnSongName;
}

void Playlist::OutputByArtist(string name) const {
	int counter = 1;
	PlaylistNode* curr = head;
	while (curr) {
		if (curr->GetArtistName() == name) {
			cout << endl << counter << ".\nUnique ID: " << curr->GetID() << "\nSong Name: " << curr->GetSongName() << "\nArtist Name: " << curr->GetArtistName() << "\nSong Length (in seconds): " << curr->GetSongLength() << endl;
		}

		counter++;
		curr = curr->next;
	}
}

void Playlist::OutputFullPlaylist(string title) const {
	cout << title << " - OUTPUT FULL PLAYLIST" << endl;
	int nodeCounter = 1;

	if (!head)
		cout << "Playlist is empty" << endl << endl;
	else {
		PlaylistNode* temp = head;
		
		while (temp) {
			cout << nodeCounter << ".\nUnique ID: " << temp->GetID() << "\nSong Name: " << temp->GetSongName() << "\nArtist Name: " << temp->GetArtistName() << "\nSong Length (in seconds): " << temp->GetSongLength() << endl << endl;

			nodeCounter++;
			temp = temp->next;
		}	
	}	
}

void Playlist::TotalTime() const {
	PlaylistNode* curr = head;
	int totalTime = 0;
	
	while (curr) {
		totalTime += curr->GetSongLength();
		curr = curr->next;
	}

	cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
	cout << "Total time: " << totalTime << endl << endl;
}
