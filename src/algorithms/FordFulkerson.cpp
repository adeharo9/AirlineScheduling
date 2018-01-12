#include "FordFulkerson.h"

// Returns the maximum flow from s to t in the given graph
int FordFulkerson::algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V)
{
	uint u, v;

	// Create a residual graph and fill the residual graph with
	// given capacities in the original graph as residual capacities
	// in residual graph
	//vector<vector<int> > residualGraph(V, vector<int>(V));

	// Residual graph where residualGraph[i][j] indicates
	// residual capacity of edge from i to j (if there
	// is an edge. If residualGraph[i][j] is 0, then there is not)
	for (u = 0; u < V; ++u)
	{
		for (v = 0; v < V; ++v)
		{
			residualGraph[u][v] = graph[u][v];
		}
	}

	vector<uint> parent(V);  // This array is filled by BFS and to store path

	int max_flow = 0;  // There is no flow initially
	// Augment the flow while there is path from source to sink
	while (travelGraph(residualGraph, s, t, parent, V))
	{
		// Find minimum residual capacity of the edges along the
		// path filled by BFS. Or we can say find the maximum flow
		// through the path found.
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, residualGraph[u][v]);
		}

		// update residual capacities of the edges and reverse edges
		// along the path
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			residualGraph[u][v] -= path_flow;
			residualGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}
	// Return the overall flow
	return max_flow;
}
