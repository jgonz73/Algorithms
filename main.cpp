/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run DFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"

using namespace std;

//
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
	vector<char> vertices = g.vertices();

	cout << "**Vertices: ";

	for (char c : vertices)
	{
		cout << c << " ";
	}

	cout << endl;

	cout << "**Edges: ";

	for (char v : vertices)
	{
		vector<char> neighbors = g.neighbors(v);


		for (char n : neighbors)
		{
			int weight = g.getweight(v, n);
			cout << "(" << v << "," << n << "," << weight << ") ";
		}
	}

	cout << endl;
}

// print out prefix then vertices from vector V
void printVertices(string prefix, const vector<char>& V)
{
	cout << prefix;
	for (char e : V)
		cout << e << " ";
	cout << endl;

}

// use stack to print out shortest path from startV to currentV
void pathOutput(char startV, char currentV, map<char, char> VertPred, map<char, int> VertWeight, vector<char> visited, int index)
{
	cout << VertWeight.at(currentV) << " via ";
	stack<char> PredStack;
	char temp;

	PredStack.push(visited[index]);

	while (index >= 1) { // iterate through map backwards
		if (VertPred.at(visited[index]) != startV)
			PredStack.push(VertPred.at(visited[index]));
		index--;
	}

	if (startV != currentV) {      // not starting vertex
		PredStack.push(visited[0]);

		while (!PredStack.empty()) { // loop through output stack
			temp = PredStack.top();
			PredStack.pop();
			if (PredStack.empty()) { // end of stack
				cout << temp << " ";
				break;
			}
			if (PredStack.top() == temp) // found duplicate
				continue;
			cout << temp << " ";


		}
		return;
	}

	cout << PredStack.top();

}

int main()
{
	vector<char>        visited;
	map<char, char>     VertPred;       // current vertex, predecessor vertex
	map<char, int>      VertWeight;     // current vertex, weight from startV
	graph  g;
	string filename;
	char   startV;

	cout << "Enter filename containing graph data> ";
	cin >> filename;

	if (filename != "graph1.txt" && filename != "graph2.txt" && filename != "graph3.txt" && filename != "graph4.txt") // invalid filename
	{
		cout << "**Error: couldn't open data file '" << filename << "'." << endl;
		return 0;
	}

	//
	// Let's input the graph, and then output to see what we have:
	//
	buildGraph(filename, g);
	outputGraph(g);


	//
	// now ask user for a starting vertex, and run algorithms
	cout << endl;
	cout << "Enter a starting vertex or #> ";
	cin >> startV;

	while (!g.isvertex(startV)) {
		cout << "Not a vertex in graph, ignored...\n";
		cout << "Enter a starting vertex or #> ";
		cin >> startV;
	}


	while (startV != '#') {

		// Neighbors 
		visited = g.neighbors(startV);
		printVertices("Neighbors: ", visited);

		// BFS Algorithm
		visited = BFS(g, startV);
		printVertices("BFS: ", visited);

		// DFS Algorithm
		visited = DFS(g, startV);
		printVertices("DFS: ", visited);

		// Dijkstra Algorithm
		visited = DijkstraShortestPath(g, startV, VertPred, VertWeight);
		printVertices("Dijkstra: ", visited);

		/*
		the part where we print out the path for each vertex
		*/
		for (size_t i = 0; i < visited.size(); i++) {
			cout << visited[i] << ": ";
			pathOutput(startV, visited[i], VertPred, VertWeight, visited, i);
			cout << endl;
		}

		if (!g.isvertex(startV)) {
			cout << "Not a vertex in graph, ignored...\n";
		}
		cout << endl;
		cout << "Enter a starting vertex or #> ";
		cin >> startV;

	}//end while()

	//
	// done:
	//
	return 0;
}
