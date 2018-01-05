#include <iostream>

#include "algorithms/EdmondsKarp.h"
#include "utils/Chrono.h"
#include "utils/Constants.h"
#include "utils/Debug.h"
#include "algorithms/FordFulkersonDFS.h"
#include "structures/Graph.h"

using namespace std;

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void version1 (Graph& graph)
{
	for (uint i = Graph::firstDestinationVertex; i < graph.vertexSize(); i += 2)	// i es desti
	{
		for (uint j = Graph::firstOriginVertex; j < graph.vertexSize(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (graph.getVertex(i).getCity() == graph.getVertex(j).getCity() and int(graph.getVertex(j).getTime()) - int(graph.getVertex(i).getTime()) >= MIN_TRANSITION_TIME)
				{
					if (i == 7 and j == 4)
					{
						cout << "Aqui estoy, con tiempo: " << graph.getVertex(j).getTime() - graph.getVertex(i).getTime() << " " << MIN_TRANSITION_TIME << endl;
						cout << "n j " << graph.getVertex(j).getTime() << " n i " << graph.getVertex(i).getTime() << endl;
					}
					// aresta del desti i al origen j amb pes 1
					graph.addNeighbour(i, Edge(i, j, 1));
				}
			}
		}
	}
}
/*
  elimina els lower bound de les arestes i actualitza les demandes
  les uniques arestes amb lower suerten de les ciutats d'origen
*/
void deleteLowerBound(Graph &graph)
{
	for (uint i = Graph::firstOriginVertex; i < graph.vertexSize(); i += Graph::originStepSize)
	{
		//la primera aresta es la del viatge
		graph.getEdge(i, Graph::sourceWithoutDemand).setCapacity(graph.getEdge(i, Graph::sourceWithoutDemand).getCapacity() - graph.getEdge(i, Graph::sourceWithoutDemand).getLowerBound());
		graph.getEdge(i, Graph::sourceWithoutDemand).setLowerBound(0);

		//sumo 1 a la demanda de l'origen, i resto 1 a la de destí
		graph.getVertex(i).incrementDemand();
		graph.getVertex(i + 1).decrementDemand();
	}
}

/*
  elimina les demandes  i actualizta el sink i drain reals amb les
  arestes necessaries
*/
void deleteDemand(Graph &graph)
{
	for (uint i = Graph::firstFlowNetworkVertex; i < graph.vertexSize(); ++i)
	{
		if (graph.getVertex(i).getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			graph.addNeighbour(i, Edge(i, 1, graph.getVertex(i).getDemand()));
			graph.getVertex(i).setDemand(0);
		}
		else if (graph.getVertex(i).getDemand() < 0)	// Si es source s va a el
		{
			graph.addNeighbour(Graph::sourceWithoutDemand, Edge(Graph::sourceWithoutDemand, i, -graph.getVertex(i).getDemand()));
			graph.getVertex(i).setDemand(0);
		}
	}
}

void transformMax(Graph &graph)
{
	vector<vector<int>> adjacenceMatrixGraph(graph.vertexSize(), vector<int>(graph.vertexSize(), 0));

	for(uint i = Graph::firstElement; i < graph.vertexSize(); ++i)
	{
		for (uint j = 0; j < graph.getEdges(i).size(); ++j)
		{
			adjacenceMatrixGraph[i][graph.getEdge(i, j).getDestination()] = graph.getEdge(i, j).getCapacity();
		}
	}

	cout << "Max Flow: " << endl;

	FordFulkerson* edmondsKarp = new EdmondsKarp();
	Chrono chrono;
	chrono.start(0);
	cout << endl << edmondsKarp -> algorithm(adjacenceMatrixGraph, 0, 1, graph.vertexSize()) << endl;
	chrono.stop(0);
	cout << "Chrono duration: " << chrono.duration(0) << endl;
	delete edmondsKarp;

	FordFulkerson* fordFulkersonDFS = new FordFulkersonDFS();
	chrono.start(1);
	cout << endl << fordFulkersonDFS -> algorithm(adjacenceMatrixGraph, 0, 1, graph.vertexSize()) << endl;
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
	Graph graph(57);

	uint maxFlights = 0;

	while (cin >> origin)	// operacions descrites a la pagina 390 del llibre
	{
		cin >> destination;
		cin >> departureTime;
		cin >> arrivalTime;

		Vertex vorigin(origin, departureTime);
		Vertex vdestination(destination, arrivalTime);

		graph.addEdge(vorigin, vdestination);

		++maxFlights;
	}

	version1(graph);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(graph);	// Eliminar els lower bound
	deleteDemand(graph);		// Eliminar les demandes

	transformMax(graph);
}
