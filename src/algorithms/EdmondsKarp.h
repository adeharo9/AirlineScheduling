#ifndef AIRLINESCHEDULING_EDMONDSKARP_H
#define AIRLINESCHEDULING_EDMONDSKARP_H

#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

// Number of vertices in given graph


/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(const vector<vector<int>> rGraph , int s, int t, int parent[],int V);

// Returns the maximum flow from s to t in the given graph
int EdmondsKarp(vector<vector<int>> rGraph, int s, int t,int V);


#endif //AIRLINESCHEDULING_EDMONDSKARP_H
