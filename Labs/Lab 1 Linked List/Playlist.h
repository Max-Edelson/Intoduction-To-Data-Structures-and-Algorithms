#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>

using namespace std;

class PlaylistNode {

	private:
		string uniqueID;
		string songName;
		string artistName;
		int songLength;

	public:
		PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), next(nullptr) {}
		PlaylistNode(string ID, string song, string name, int length, PlaylistNode* n) : uniqueID(ID), songName(song), artistName(name), songLength(length), next(n) {}
		PlaylistNode(const char* ID, const char* name, const char* artist, int length) : uniqueID(ID), songName(name), artistName(artist), songLength(length) {}
		void InsertAfter(PlaylistNode* after) { 
			PlaylistNode* temp = this->next;
			this->next = after;
		        after->next = temp;
		}
		void SetNext(PlaylistNode* n) { this->next = n; }
		string GetID() { return uniqueID; }
		string GetSongName() { return songName; }
		string GetArtistName() { return artistName; }
		int GetSongLength() { return songLength; }
		PlaylistNode* GetNext() { return next; }
		void PrintPlaylistNode() { cout << "Unique ID: " << uniqueID << "\nSong Name: " << songName << "\nArtist Name: " << artistName << "\nSong Length (in seconds): " << songLength << endl; }
		PlaylistNode* next;
};


class Playlist {
	
	private:
		PlaylistNode* head;
		PlaylistNode* tail;
	
	public:
		Playlist() : head(nullptr), tail(nullptr) {}
		~Playlist();
		void AddSong(string ID, string sName, string aName, int length);
		string RemoveSong(string ID);
		string ChangePosition(int currPosition, int desired);
		void OutputByArtist(string name) const;
		void OutputFullPlaylist(string title) const;
		void TotalTime() const;

};   

#endif
