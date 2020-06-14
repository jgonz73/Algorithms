/*Dijkstra.cpp*/

#include "Dijkstra.h"

vector<char> DijkstraShortestPath(graph& g, char startV)
{
	vector<char>        visited;        // vector of visted vertices
	minqueue<char, int> unvisitedQueue; // minqueue of unvisited vertices and their weight
	vector<char>        allVertices = g.vertices(); // vector of all the vertices in graph g
	map<char, char>     VertPred;       // current vertex, predecessor vertex
	map<char, int>      VertWeight;     // current vertext, weight

	int edgeWeight = 0;
	int alternativePathDistance = 0;

	for (char vertex : allVertices) {   // vertex 
		VertWeight.emplace(vertex, Infinity);
		VertPred.emplace(vertex, -1);
		unvisitedQueue.pushinorder(vertex, Infinity);
	}

	// startV has a distance of 0 from itself
	VertWeight.at(startV) = 0;
	unvisitedQueue.pushinorder(startV, 0);

	while (unvisitedQueue.empty()) {
		// Visit vertex with minimum distance from startV
		char currentV = unvisitedQueue.minfront();
		unvisitedQueue.minpop();
		if (VertWeight.at(currentV) == Infinity)
			break;
		visited.push_back(currentV);

		vector<char> neighborV = g.neighbors(currentV); // tracks neighboring vectors to currentV
		for (char adjV : neighborV) {
		   edgeWeight = g.getweight(currentV, adjV);
		   alternativePathDistance = VertWeight.at(currentV) + edgeWeight;
		   
		   // If shorter path from startV to adjV is found,
		   // update adjV's distance and predecessor
		   if (alternativePathDistance < VertWeight.at(adjV)) {
			    VertWeight.at(adjV) = alternativePathDistance;
				VertPred.at(adjV) = currentV;
			}
		}//end for

	}//end while
	return visited;
}
