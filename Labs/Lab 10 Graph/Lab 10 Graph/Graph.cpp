#include "Graph.h"

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <iterator>

using namespace std;

Graph::Graph() {}
Graph::Graph(ifstream& input) {

	if (input.is_open()) {
		int vertexCount = 0;
		int edgeCount = 0;
		input >> vertexCount;
		input >> edgeCount;

		string vertexName;

		for (int i = 0; i < vertexCount; i++) {
			input >> vertexName;
			Vertex vertex = Vertex(vertexName);
			vertices.push_back(vertex);
		}


		string vertexA;
		string vertexB;
		int vertexAPos;
		int vertexBPos;
		int cost;

		for (int i = 0; i < edgeCount; i++) {
			input >> vertexA;
			input >> vertexB;
			input >> cost;

			for (unsigned j = 0; j < vertices.size(); j++) {
				if (vertices.at(j).label == vertexA) {
					vertexAPos = j;
				}
				else if (vertices.at(j).label == vertexB) {
					vertexBPos = j;
				}
			}

			pair <int, int> neighbor;
			neighbor.second = cost;

			for (unsigned k = 0; k < vertices.size(); k++) {
				if (vertices.at(k).label == vertexA) {
					neighbor.first = vertexBPos;
					vertices.at(k).neighbors.push_back(neighbor);
				}
				else if (vertices.at(k).label == vertexB) {
					neighbor.first = vertexAPos;
					vertices.at(k).neighbors.push_back(neighbor);
				}
			}
		}
	}
	else {
		cout << "Error: File couldn't open" << endl;
	}
}

Graph::~Graph() {}

void Graph::bfs() {

	queue<int>	queue;

	queue.push(0);
	vertices.at(0).distance = 0;

	while (!queue.empty()) {
		int u = queue.front();
		queue.pop();

		int target;

		list< pair<int,int> >::iterator itList;
		for (itList = vertices.at(u).neighbors.begin(); itList != vertices.at(u).neighbors.end(); itList++) {
			target = itList->first;
			if (vertices.at(target).color == "WHITE") {
				vertices.at(target).color = "GREY";
				vertices.at(target).distance = vertices.at(u).distance + 1;
				//vertices.at(target).prev->u;
				vertices.at(target).prev = &vertices.at(u);
				queue.push(target);
			}
		}
		vertices.at(u).color = "BLACK";
	}
	printGraph();
}

void Graph::printGraph() const {
	for (unsigned i = 0; i < vertices.size(); i++) {
		cout << "Name: " << vertices.at(i).label << " Color: " << vertices.at(i).color << " Distance: " << vertices.at(i).distance << endl;
	}

	cout << endl;

	for (unsigned i = 0; i < vertices.size(); i++) {
		cout << vertices.at(i).label << endl;
	}
	
	for (unsigned i = 0; i < vertices.size(); i++) { 
		list< pair<int,int> >::const_iterator itList;
		for (itList = vertices.at(i).neighbors.begin(); itList != vertices.at(i).neighbors.end(); itList++) {
			cout << vertices.at(i).label << " " << vertices.at(itList->first).label << " " << itList->second << endl;
		}
	}
}

void Graph::output_graph(const string& filename, const Vertex start) {
	for	(unsigned i = 0; i < vertices.size(); i++) {
		list< pair<int, int> >::iterator itList;
	}
}

void Graph::output_graph(const string& filename) {
	/*ofstream outFS(filename.c_str());
	if (!outFS.is_open()) {
		cout << "Error opening " << filename << endl;
		return;
	}
	outFS << "digraph G {" << endl;
	output_graph(filename, vertices.at(0));
	outFS << "}";
	outFS.close();
	string jpgFilename = filename.substr(0, filename.size() - 4) + ".jpg";
	string command = "dot -Tjpg " + filename + " -o " + jpgFilename;
	system(command.c_str());*/
}
