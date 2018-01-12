#include "DinicBlockingFlow.h"

const string DinicBlockingFlow::ID = "DI";

bool DinicBlockingFlow::buildLevelGraph(uint s, uint t, vector<vector<int> > &residualGraph, vector<int> &levels)
{
	int V = residualGraph.size();

	for (int i = 0 ; i < V ; ++i)	// set all levels to -1 (also mark all vertices as not visited)
	{
		levels[i] = -1;
	}
 
    levels[s] = 0;  // level of source vertex

    queue<int> visiting;	// create a queue and enqueue source vertex
    visiting.push(s);
 
    while (!visiting.empty()){
        int u = visiting.front();
        visiting.pop();

        for (int v = 0; v < V; v++)	//for all vertices adjacent to u
		{
            if (levels[v] < 0 and residualGraph[u][v] > 0)
			{
                levels[v] = levels[u] + 1;	// level of current vertex is level of parent + 1
 
                visiting.push(v);
            }
        }
    }
    return levels[t] >= 0;	// return if t has been reached
}

int DinicBlockingFlow::blockingFlow(uint u, int flow, uint t, vector<int> &lastAdjacent, vector<vector<int> > &residualGraph, vector<int> &levels)
{
    if (u == t)	// sink reached
	{
		return flow;
	}
    
    int V = residualGraph.size();

    for ( ; lastAdjacent[u] < V; ++lastAdjacent[u])	// for all adjacent vertices from the last one visited
	{

		int v = lastAdjacent[u];

        if (residualGraph[u][v] > 0 and levels[v] == levels[u]+1)	//if u - v edge has residual capacity and v has the level of u plus 1
		{
            flow = min(flow, residualGraph[u][v]);	// find minimum flow from u to t
 
            int auxflow = blockingFlow(v, flow, t, lastAdjacent, residualGraph, levels);

            if (auxflow > 0)
			{
				flow = auxflow;
				residualGraph[u][v] -= flow;
				residualGraph[v][u] += flow;
                return flow;
            }
        }
    }
    return 0;
}

int DinicBlockingFlow::algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V)
{
    vector<int> levels(V, 0);
	residualGraph = vector<vector<int>>(V, vector<int>(V));

	for (int u = 0; u < V; ++u)	// create the residual graph
	{
		for (int v = 0; v < V; ++v)
		{
			residualGraph[u][v] = graph[u][v];
		}
	}
 
    int max_flow = 0;

    while (buildLevelGraph(s, t, residualGraph, levels))	// build the new level graph and augment max flow while there is a s - t path
	{
        vector<int> lastAdjacent(V, 0);	// last adjacent vertex visited
 
		int flow = blockingFlow(s, INT_MAX, t, lastAdjacent, residualGraph, levels); // get flow of the first path

        while (flow != 0)	// while blocking flow not reached
		{
            max_flow += flow;	// add path flow to total flow
            
            flow = blockingFlow(s, INT_MAX, t, lastAdjacent, residualGraph, levels); // get next path flow
		}
    }
 
    // return maximum flow
    return max_flow;
}
