/*DFS.cpp*/

#include "DFS.h"


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
  char     v;

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
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}

