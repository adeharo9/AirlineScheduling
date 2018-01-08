#include "Debug.h"

void Debug::printState(const vector<Vertex>& n, const vector<vector<Edge> >& g)
{
	for(int i = 0; i < n.size(); ++i)
	{
		switch(i)
		{
			case 0:
				cout << "Real source: " << endl;
				break;

			case 1:
				cout << "Real sink: " << endl;
				break;

			case 2:
				cout << "Demands source: " << endl;
				break;

			case 3:
				cout << "Demands sink: " << endl;
				break;

			default:
				cout << endl << "Vertex " << i;

				if (i % 2 == 0)
				{
					cout << " (Origen)";
				}
				else
				{
					cout << " (Destí)";
				}

				cout << ": " << endl;
				cout << "(Ciutat: " << n[i].getCity() << ", Hora: " << n[i].getTime() << ", Demanda: " << n[i].getDemand() << ")" << endl;
				break;
		}
		for (int j = 0; j < g[i].size(); ++j)
		{
			cout << "Edge" << j << ": ";
			cout << "(" << g[i][j].getDestination() << ", low: " << g[i][j].getLowerBound() << ", capacity: " << g[i][j].getCapacity() << " )" << endl;
		}
	}
}

void Debug::printGraph(Graph &graph)
{
	vector<vector<int> > adjacenceMatrixGraph(graph.vertexSize(), vector<int>(graph.vertexSize(), 0));

	for (uint i = Graph::firstElement; i < graph.vertexSize(); ++i)
	{
		for (uint j = 0; j < graph.getEdges(i).size(); ++j)
		{
			adjacenceMatrixGraph[i][graph.getEdge(i, j).getDestination()] = graph.getEdge(i, j).getCapacity();
		}
	}

	for (uint u = 0; u < adjacenceMatrixGraph.size(); ++u)
	{
		if (u == 4)
		{
			cout << "--------------------------------" << endl;
		}

		for (uint v = 0; v < adjacenceMatrixGraph[0].size(); ++v)
		{
			if (v == 4)
			{
				cout << '|';
			}

			cout << adjacenceMatrixGraph[u][v] << " ";
		}
		cout << endl;
	}
}