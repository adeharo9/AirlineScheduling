// C++ program for implementation of Edmonds Karp algorithm

#include "EdmondsKarp.h"

void print_sol(const vector<vector<int>> &g,const vector<vector<int>> &ini){
	cout<<"Resultat: "<<endl<<endl;
	//si s'ha seguit una aresta amb capacitat 1, al graf final te capacitat 0
	int p=1;
	int size=g.size();
	for(int i=4;i<size;i+=2){//origen
		if (g[2][i]==0){//si el camí comença per el vertex i
			cout<<"Pilot: "<<p<<endl;
			int j=i;
			//index segons l'exemple de l'enunciat
			while(g[j+1][3]!=0){// si NO es l'ultim vol que fa el pilot
				cout<<"	Vol: "<<(j-4)/2+1<<endl;
				bool found=false;
				for(int k=4;k<size and not found;k+=2){
					if(g[j+1][k]==0 and ini[j+1][k]==1){//si el vol ha seguit per aquest camí
						j=k;
						found=true;
					}
				}
			}
			cout<<"        Vol: "<<(j-4)/2+1<<endl<<endl;
			p++;
		}
	}
}

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(const vector<vector<int>> &rGraph, int s, int t, int parent[],int V)
{
	// Create a visited array and mark all vertices as not visited
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source vertex
	// as visited
	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v=0; v<V; v++)
		{
			if (visited[v]==false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// If we reached sink in BFS starting from source, then return
	// true, else false
	return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
int EdmondsKarp(vector<vector<int>> & graph, int s, int t,int V)
{
	int u, v;

	// Create a residual graph and fill the residual graph with
	// given capacities in the original graph as residual capacities
	// in residual graph
	vector<vector<int>> rGraph(V,vector<int>(V));
	// Residual graph where rGraph[i][j] indicates
					 // residual capacity of edge from i to j (if there
					 // is an edge. If rGraph[i][j] is 0, then there is not)
	for (u = 0; u < V; u++){
		if (u==4)cout<<"----------------------"<<endl;

		for (v = 0; v < V; v++){
			if (v==4)cout<<'|';

			 rGraph[u][v] = graph[u][v];
			 cout<<graph[u][v]<<" ";
		   }
			 cout<<endl;
		   }

	int parent[V];  // This array is filled by BFS and to store path

	int max_flow = 0;  // There is no flow initially
	// Augment the flow while tere is path from source to sink
	while (bfs(rGraph, s, t, parent,V))
	{
		// Find minimum residual capacity of the edges along the
		// path filled by BFS. Or we can say find the maximum flow
		// through the path found.
		int path_flow = INT_MAX;
		for (v=t; v!=s; v=parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// update residual capacities of the edges and reverse edges
		// along the path
		for (v=t; v != s; v=parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}
	// Return the overall flow
// TODO hacer una funcion para print y que no sea tan cutre

	cout<<"Final"<<endl<<endl;
	for (u = 0; u < V; u++){
		if (u==4)cout<<"----------------------"<<endl;
		for (v = 0; v < V; v++){
			if (v==4)cout<<'|';
			 cout<<rGraph[u][v]<<" ";
		   }
			 cout<<endl;
	}

	//si el resultat es solució, el flow al T real ha de ser k + nombre de vols
	int k=graph[3][1]; //un lloc on es troba k
	int nvols=(graph.size()-4)/2;
	int flow=0;
	if (rGraph[3][1]==0)flow=k;
	for (int i=4;i<graph.size();i+=2){
		if(rGraph[i][1]==0)flow++;
	}
	if (flow==nvols+k) print_sol(rGraph,graph);
	else cout<<"No s'ha trobat cap solució"<<endl;
	return max_flow;
}
