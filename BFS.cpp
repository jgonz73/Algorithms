/*util.cpp*/

#include "BFS.h"


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
     for (size_t i=0; i<neighborV.size(); i++) { // loop through to access and discover neighborV's
  
		if (discoveredSet.find(neighborV[i]) == discoveredSet.end()) { // v is not an element of the discoveredSet
           frontierQueue.push(neighborV[i]);
           discoveredSet.insert(neighborV[i]);
        }

     }//end for

  }//end while
  
  return visited;
}

