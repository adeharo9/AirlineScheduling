#ifndef AIRLINESCHEDULING_EDMONDSKARP_H
#define AIRLINESCHEDULING_EDMONDSKARP_H

#include <iostream>
#include <climits>
#include <cstring>
#include <queue>

using namespace std;

// Number of vertices in given graph
#define V 16

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int rGraph[V][V], int s, int t, int parent[]);

// Returns the maximum flow from s to t in the given graph
int EdmondsKarp(int **graph, int s, int t);


#endif //AIRLINESCHEDULING_EDMONDSKARP_H
