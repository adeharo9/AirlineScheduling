#include <iostream>
//#include <vector>

#include "algorithms/EdmondsKarp.h"
#include "utils/Chrono.h"
#include "utils/Constants.h"
#include "utils/Debug.h"
//#include "utils/Utils.h"
//#include "structures/Edge.h"
//#include "structures/Vertex.h"
#include "algorithms/FordFulkersonDFS.h"
#include "structures/Graph.h"

using namespace std;

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
//void version1 (const vector<Vertex>& nodes, vector<vector<Edge>>& graph, Graph& data)
void version1 (Graph& data)
{
	/*for (uint i = 5; i < nodes.size(); i += 2)	// i es desti
	{
		for (uint j = 4; j < nodes.size(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (nodes[i].getCity() == nodes[j].getCity() and int(nodes[j].getTime()) - int(nodes[i].getTime()) >= MIN_TRANSITION_TIME)
				{
					if (i == 7 and j == 4)
					{
						cout << "Aqui estoy, con tiempo: " << nodes[j].getTime() - nodes[i].getTime() << " " << MIN_TRANSITION_TIME << endl;
						cout << "n j " << nodes[j].getTime() << " n i " << nodes[i].getTime() << endl;
					}
					// aresta del desti i al origen j amb pes 1
					graph[i].emplace_back(Edge(i, j, 1));
				}
			}
		}
	}*/

	for (uint i = Graph::firstDestinationVertex; i < data.vertexSize(); i += 2)	// i es desti
	{
		for (uint j = Graph::firstOriginVertex; j < data.vertexSize(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (data.getVertex(i).getCity() == data.getVertex(j).getCity() and int(data.getVertex(j).getTime()) - int(data.getVertex(i).getTime()) >= MIN_TRANSITION_TIME)
				{
					if (i == 7 and j == 4)
					{
						cout << "Aqui estoy, con tiempo: " << data.getVertex(j).getTime() - data.getVertex(i).getTime() << " " << MIN_TRANSITION_TIME << endl;
						cout << "n j " << data.getVertex(j).getTime() << " n i " << data.getVertex(i).getTime() << endl;
					}
					// aresta del desti i al origen j amb pes 1
					data.addNeighbour(i, Edge(i, j, 1));
				}
			}
		}
	}
}
/*
  elimina els lower bound de les arestes i actualitza les demandes
  les uniques arestes amb lower suerten de les ciutats d'origen
*/
//void deleteLowerBound(vector<Vertex> &nodes, vector<vector<Edge>> &graph, Graph &data)
void deleteLowerBound(Graph &data)
{
	/*for (uint i = 4; i < nodes.size(); i += 2)
	{
		//la primera aresta es la del viatge
		graph[i][0].setCapacity(graph[i][0].getCapacity() - graph[i][0].getLowerBound());
		graph[i][0].setLowerBound(0);

		//sumo 1 a la demanda de l'origen, i resto 1 a la de destí
		nodes[i].incrementDemand();
		nodes[i + 1].decrementDemand();
	}*/

	for (uint i = Graph::firstOriginVertex; i < data.vertexSize(); i += Graph::originStepSize)
	{
		//la primera aresta es la del viatge
		data.getEdge(i, Graph::sourceWithoutDemand).setCapacity(data.getEdge(i, Graph::sourceWithoutDemand).getCapacity() - data.getEdge(i, Graph::sourceWithoutDemand).getLowerBound());
		data.getEdge(i, Graph::sourceWithoutDemand).setLowerBound(0);

		//sumo 1 a la demanda de l'origen, i resto 1 a la de destí
		data.getVertex(i).incrementDemand();
		data.getVertex(i + 1).decrementDemand();
	}
}

/*
  elimina les demandes  i actualizta el sink i drain reals amb les
  arestes necessaries
*/
//void deleteDemand(vector<Vertex> &nodes, vector<vector<Edge>> &graph, Graph &data)
void deleteDemand(Graph &data)
{
	/*for (uint i = 2; i < nodes.size(); ++i)
	{
		if (nodes[i].getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			graph[i].emplace_back(Edge(i, 1, nodes[i].getDemand()));
			nodes[i].setDemand(0);
		}
		else if (nodes[i].getDemand() < 0)	// Si es source s va a el
		{
			graph[0].emplace_back(Edge(0, i, -nodes[i].getDemand()));
			nodes[i].setDemand(0);
		}
	}*/

	for (uint i = Graph::firstFlowNetworkVertex; i < data.vertexSize(); ++i)
	{
		if (data.getVertex(i).getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			data.addNeighbour(i, Edge(i, 1, data.getVertex(i).getDemand()));
			data.getVertex(i).setDemand(0);
		}
		else if (data.getVertex(i).getDemand() < 0)	// Si es source s va a el
		{
			data.addNeighbour(Graph::sourceWithoutDemand, Edge(Graph::sourceWithoutDemand, i, -data.getVertex(i).getDemand()));
			data.getVertex(i).setDemand(0);
		}
	}
}

//void transformMax(vector<Vertex> &n, vector<vector<Edge>> &g, Graph &data)
void transformMax(Graph &data)
{
	/*vector<vector<int>> graph(n.size(), vector<int>(n.size(), 0));

	for(uint i = 0; i < n.size(); ++i)
	{
		for (uint j = 0; j < g[i].size(); ++j)
		{
			graph[i][g[i][j].getDestination()] = g[i][j].getCapacity();
		}
	}*/

	vector<vector<int>> graph(data.vertexSize(), vector<int>(data.vertexSize(), 0));

	for(uint i = Graph::firstElement; i < data.vertexSize(); ++i)
	{
		for (uint j = 0; j < data.getEdges(i).size(); ++j)
		{
			graph[i][data.getEdge(i, j).getDestination()] = data.getEdge(i, j).getCapacity();
		}
	}

	cout << "Max Flow: " << endl;

	FordFulkerson* edmondsKarp = new EdmondsKarp();
	Chrono chrono;
	chrono.start(0);
	//cout << endl << edmondsKarp -> algorithm(graph, 0, 1, n.size()) << endl;
	cout << endl << edmondsKarp -> algorithm(graph, 0, 1, data.vertexSize()) << endl;
	chrono.stop(0);
	cout << "Chrono duration: " << chrono.duration(0) << endl;
	delete edmondsKarp;

	FordFulkerson* fordFulkersonDFS = new FordFulkersonDFS();
	chrono.start(1);
	//cout << endl << fordFulkersonDFS -> algorithm(graph, 0, 1, n.size()) << endl;
	cout << endl << fordFulkersonDFS -> algorithm(graph, 0, 1, data.vertexSize()) << endl;
	chrono.stop(1);
	cout << "Chrono duration: " << chrono.duration(1) << endl;
	delete fordFulkersonDFS;
}

int main ()
{
	uint origin;
	uint destination;
	uint departureTime;
	uint arrivalTime;

	// estructura de dades per guardar les arestes
	// graf [0] source without demands
	// graf [1] sink without demands
	// graf [2] source with demands
	// graf [3] sink with demands
	//vector<vector<Edge>> graph(MIN_VERTICES);	// sources and sinks
	//vector<Vertex> nodes(MIN_VERTICES);			// nodes
	Graph data;

	uint i = 4;

	while (cin >> origin)	// operacions descrites a la pagina 390 del llibre
	{
		cin >> destination;
		cin >> departureTime;
		cin >> arrivalTime;

		Vertex vorigin(origin, departureTime);
		Vertex vdestination(destination, arrivalTime);

		data.addEdge(vorigin, vdestination);

		/*nodes.emplace_back(Vertex(origin, departureTime));				// Afegeix el node de la ciutat d'origen
		nodes.emplace_back(Vertex(destination, arrivalTime));			// Afegeix el node de la ciutat de destí

		graph.emplace_back(vector<Edge>(1, Edge(i, i + 1, 1, 1)));		// Afegeix l'aresta entre vols

		graph[2].emplace_back(Edge(2, i, 1));							// Afegeix l'aresta del source al origen
		graph.emplace_back(vector<Edge>(1, Edge(i + 1, 3, 1)));			// Afegeix l'aresta del desti al sink*/

		i += 2;
	}

	int k = 2;

	data.addNeighbour(Graph::sourceWithDemand, Edge(Graph::sourceWithDemand, Graph::sinkWithDemand, k));
	data.getVertex(Graph::sourceWithDemand).setDemand(-k);
	data.getVertex(Graph::sinkWithDemand).setDemand(k);

	/*graph[2].emplace_back(Edge(2, 3, k));
	nodes[2].setDemand(-k);
	nodes[3].setDemand(k);*/

	/*version1(nodes, graph, data);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(nodes, graph, data);	// Eliminar els lower bound
	deleteDemand(nodes, graph, data);		// Eliminar les demandes

	transformMax(nodes, graph, data);*/

	version1(data);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(data);	// Eliminar els lower bound
	deleteDemand(data);		// Eliminar les demandes

	transformMax(data);
	//Debug::printState(nodes, graph);
}
