#include "FordFulkersonDFS.h"

const string FordFulkersonDFS::ID = "FF_DFS";

int FordFulkersonDFS::fordFulkersonDFS(vector<vector<int> > &residualGraph, uint s, uint t, uint V)
{
	return algorithm(residualGraph, s, t, V);
}

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent to store the path */
bool FordFulkersonDFS::travelGraph(const vector<vector<int> > &residualGraph, uint s, uint t, vector<uint> &parent, uint V)
{
	vector<bool> visited(V, false);	// Create a visited array and mark all vertices as not visited
	stack<uint> visiting;			// Create a queue, enqueue source vertex and mark source vertex as visited

	visited[s] = true;
	visiting.push(s);
	parent[s] = UINT_MAX;

	while (not visiting.empty())
	{
		uint current = visiting.top();
		visiting.pop();

		for (uint neighbour = 0; neighbour < V; ++neighbour)
		{
			if (not visited[neighbour] and residualGraph[current][neighbour] > 0)
			{
				visited[neighbour] = true;
				visiting.push(neighbour);
				parent[neighbour] = current;
			}
		}
	}

	return visited[t];	// If we reached sink in BFS starting from source, then return true
}