#include <iostream>
#include<ios>
#include<limits>
#include "Playlist.h"

using namespace std;

void PrintMenu(string title) {
	cout << title << " PLAYLIST MENU" << endl;
	cout << "a - Add song\nd - Remove song\nc - Change position of song\ns - Output songs by specific artist\nt - Output total time of playlist (in seconds)\no - Output full playlist\nq - Quit\n\n";
	cout << "Choose an option:";
}

int main() {
	string playlistTitle;
	char input;

	Playlist playlist;

	cout << "Enter playlist's title:" << endl << endl;
	getline(cin, playlistTitle);
	cin.clear();	

	PrintMenu(playlistTitle);
	cin >> input;
	cin.clear();
	
	while (true) {
		switch (input) {
			case 'q': {
				cout << endl;
				return 0;
				} break;

			case 'a': {
				string ID;
				string sName;
				string aName;
				string clear;
				int time = 0;
				cout << "ADD SONG" << endl;
				cout << "Enter song's unique ID:";
				cin >> ID;
				cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
				cout << endl << "Enter song's name:";
				getline(cin, sName);
				cout << endl << "Enter artist's name:";
				getline(cin, aName);
				cout << endl << "Enter song's length (in seconds):";
				cin.clear();
				cin >> time;
				cout << endl << endl;

				playlist.AddSong(ID, sName, aName, time);
				} break;
			
			case 'd': {
				string rID;
				cout << "REMOVE SONG" << endl;
				cout << "Enter song's unique ID:" << endl;
				cin >> rID;
				
				cout << '"';
				cout << playlist.RemoveSong(rID);
				cout << '"';
				cout << " removed." << endl << endl;
				} break;

			case 'c': {
				int currPos = 0;
				int desiredPos = 0;
				cout << endl << "CHANGE POSITION OF SONG" << endl;
				cout << "Enter song's current position:" << endl;
				cin >> currPos;
				cout << "Enter new position for song:" << endl;
				cin >> desiredPos;
				cout << '"' << playlist.ChangePosition(currPos, desiredPos) << '"' << " moved to position " << desiredPos << endl << endl;
				} break;

			case 's': {
				string userInput;
				cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
				cout << "Enter artist's name:" << endl;
				cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
				getline(cin, userInput);
				cin.clear();
				playlist.OutputByArtist(userInput);	
				} break;
			case 't': {
				playlist.TotalTime();
				} break;
			case 'o': {
				playlist.OutputFullPlaylist(playlistTitle);				
				} break;
		}	
		
		PrintMenu(playlistTitle);
        	cin >> input;
		cin.clear();
	}

}
