/*DFS.h*/

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"

using namespace std;

void buildGraph(string filename, graph& g);
vector<char> DFS(graph& g, char startV);
