/*util.cpp*/

#include "util.h"


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
	ifstream file(filename);

	if (!file.good())
	{
		cout << endl;
		cout << "**Error: unable to open input file '" << filename << "'." << endl;
		cout << endl;
		return;
	}

	//
	// Input vertices as single uppercase letters:  A B C ... #
	//

	string input;
	file >> input;
	while (input != "#") {
		char vertex = input[0];
		g.addvertex(vertex);
		file >> input;
	}

	//
	// Now input edges:  Src Dest Weight ... #
	//

	string from, to, weight;
	file >> from;
	while (from != "#") {
		file >> to;
		file >> weight;
		g.addedge(from[0], to[0], stoi(weight));

		file >> from;
	}

}



//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
	vector<char>  neighborV; // vector with neighboring vertices to currentV
	vector<char>  visited;   // vector with visited vertices
	queue<char>   frontierQueue;
	set<char>     discoveredSet;

	frontierQueue.push(startV);
	discoveredSet.insert(startV);

	while (frontierQueue.empty() == false) { // loop through graph
		char currentV = frontierQueue.front(); // take vertex from front of queue and pop queue
		frontierQueue.pop();
		visited.push_back(currentV);

		neighborV = g.neighbors(currentV); // find neighbors to currentV
		for (size_t i = 0; i < neighborV.size(); i++) { // loop through to access and discover neighborV's

			if (discoveredSet.find(neighborV[i]) == discoveredSet.end()) { // v is not an element of the discoveredSet
				frontierQueue.push(neighborV[i]);
				discoveredSet.insert(neighborV[i]);
			}

		}//end for

	}//end while

	return visited;
}

//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
	vector<char>  visited;        // tracks visited vertices
	stack<char>   frontierStack;
	set<char>     visitedSet;     // tracks visited vertices and has find method 

	frontierStack.push(startV);

	while (!frontierStack.empty()) { // loops through remaining vertices in graph g

		char curV = frontierStack.top();
		frontierStack.pop();

		// adds curV to visited in order that vertices were visited
		if (visitedSet.find(curV) == visitedSet.end()) { // then v is not an element of the set:
			visited.push_back(curV);
			visitedSet.insert(curV);
			vector<char> adjacentV = g.neighbors(curV);

			for (char adjV : adjacentV) {
				frontierStack.push(adjV);
			}

		}//end if
	}//end while

	return visited;
}

vector<char> DijkstraShortestPath(graph& g, char startV, map<char, char>& VertPred, map<char, int>& VertWeight)
{
	vector<char>        visited;        // vector of visted vertices
	minqueue<char, int> unvisitedQueue; // minqueue of unvisited vertices and their weight
	vector<char>        allVertices = g.vertices(); // vector of all the vertices in graph g

	int edgeWeight = 0;
	int alternativePathDistance = 0;

	for (char vertex : allVertices) {   // initializes predecessor and weight maps
		VertWeight[vertex] = Infinity;
		VertPred[vertex] = -1;
		unvisitedQueue.pushinorder(vertex, Infinity);
	}

	// startV has a distance of 0 from itself
	VertWeight.at(startV) = 0;
	unvisitedQueue.pushinorder(startV, 0);

	while (!unvisitedQueue.empty()) {
		char currentV = unvisitedQueue.minfront(); // Visit vertex with minimum distance from startV
		unvisitedQueue.minpop();
		if (VertWeight.at(currentV) == Infinity)   // found vertex that is unreachable, break
			break;
		visited.push_back(currentV);

		vector<char> neighborV = g.neighbors(currentV); // tracks neighboring vectors to currentV
		for (char adjV : neighborV) {
			edgeWeight = g.getweight(currentV, adjV);
			alternativePathDistance = VertWeight.at(currentV) + edgeWeight;

			if (alternativePathDistance < VertWeight.at(adjV)) { // shorter path from startV to adjV
				VertWeight.at(adjV) = alternativePathDistance;
				VertPred.at(adjV) = currentV;
				unvisitedQueue.pushinorder(adjV, alternativePathDistance);
			}
		}//end for

	}//end while
	return visited;
}
