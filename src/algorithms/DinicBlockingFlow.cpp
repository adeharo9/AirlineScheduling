#include "DinicBlockingFlow.h"

const string DinicBlockingFlow::ID = "DI";

bool DinicBlockingFlow::buildLevelGraph(uint s, uint t, vector<vector<int> > &residualGraph, vector<int> &levels){
/*	int V = residualGraph.size();
	
	// set all levels to -1 (also mark all vertices as not visited)
	for (int i = 0 ; i < V ; i++) levels[i] = -1;
 
    levels[s] = 0;  // level of source vertex
 
    // create a queue and enqueue source vertex
    queue<int> q;
    q.push(s);
 
    while (!q.empty()){
        int u = q.front();
        q.pop();
        
        //for all vertices adjacent to u
        for (int v = 0; v < V; v++){
			
            if (levels[v] < 0 and residualGraph[u][v] > 0){
                // level of current vertex is level of parent + 1
                levels[v] = levels[u] + 1;
 
                q.push(v);
            }
        }
    }
 
    // return if t has been reached
    return levels[t] >= 0;*/
    return false;
}

int DinicBlockingFlow::blockingFlow(uint u, int flow, uint t, vector<int> &lastAdjacent, vector<vector<int> > &residualGraph, vector<int> &levels){
	/*// sink reached
    if (u == t){
		//cout << "base " << u << " " << t << endl;
		return flow;
	}
    
    int V = residualGraph.size();
 
		//cout << "enters function: " << V << endl;
    // for all adjacent vertices from the last one visited
    for ( ; lastAdjacent[u] < V; ++lastAdjacent[u]){
		
		//cout << "loop: " << lastAdjacent[u] << endl;
		int v = lastAdjacent[u];
		
		//if u - v edge has residual capacity and v has the level of u plus 1
		//cout << u << ' ' << v << ' '<<residualGraph[u][v] << endl;
        if (residualGraph[u][v] > 0 and levels[v] == levels[u]+1) {
			//cout << "next: " << v << endl;
			
            // find minimum flow from u to t
            flow = min(flow, residualGraph[u][v]);
 
            flow = blockingFlow(v, flow, t, lastAdjacent, residualGraph, levels);
			//cout << "out" << flow << endl;
            if (flow > 0){
				
				residualGraph[u][v] -= flow;
				residualGraph[v][u] += flow;
                return flow;
            }
        }
    }
 
    return 0;*/
    return 0;
}

int DinicBlockingFlow::algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V){
	/*cout << "target: " << s << endl;
	cout << "target: " << t << endl;
	    
    vector<int> levels(V, 0);
    
    // create the residual graph
	for (int u = 0; u < V; ++u){
		for (int v = 0; v < V; ++v){
			residualGraph[u][v] = graph[u][v];
		}
	}
 
    int max_flow = 0;
 
    // build the new level graph and augment max flow while there is a s - t path 
    while (buildLevelGraph(s, t, residualGraph, levels)){
        // last adjacent vertex visited
        vector<int> lastAdjacent(V, 0);
 
		int flow = blockingFlow(s, INT_MAX, t, lastAdjacent, residualGraph, levels); // get flow of the first path
		
		
		cout << "flow:" << flow << endl;
		int j=0;
        // while blocking flow not reached
        while (flow){
        cout << "ntra wehilw;" << j << endl;
        j++;
            // add path flow to total flow
            max_flow += flow;
            
            flow = blockingFlow(s, INT_MAX, t, lastAdjacent, residualGraph, levels); // get next path flow
            
            cout << "flow after:" << flow << endl;
		}
    }
 
    // return maximum flow
    return max_flow;*/
    return 2;
}
