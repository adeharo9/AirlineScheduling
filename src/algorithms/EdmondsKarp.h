#ifndef AIRLINESCHEDULING_EDMONDSKARP_H
#define AIRLINESCHEDULING_EDMONDSKARP_H

#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>

typedef unsigned int uint;

using namespace std;

// Traces back and prints the solution

void print_sol(const vector<vector<int>> & g,const vector<vector<int>> &ini);

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(const vector<vector<int>> &rGraph , uint s, uint t, vector<int> &parent, uint V);

// Returns the maximum flow from s to t in the given graph
int edmondsKarp(vector<vector<int>> &rGraph, uint s, uint t, uint V);


#endif //AIRLINESCHEDULING_EDMONDSKARP_H
