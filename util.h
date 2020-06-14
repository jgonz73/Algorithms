/*util.h*/

#pragma once


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <map>
#include <limits>

#include "graph.h"
#include "minqueue.h"

using namespace std;

const int Infinity = numeric_limits<int>::max();

void buildGraph(string filename, graph& g);
vector<char> DijkstraShortestPath(graph& g, char startV, map<char, char>& VertPred, map<char, int> VertWeight);
vector<char> BFS(graph& g, char startV);
vector<char> DFS(graph& g, char startV);