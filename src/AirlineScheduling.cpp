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
void version1 (Graph& data)
{
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
void deleteLowerBound(Graph &data)
{
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
void deleteDemand(Graph &data)
{
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

void transformMax(Graph &data)
{
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
	cout << endl << edmondsKarp -> algorithm(graph, 0, 1, data.vertexSize()) << endl;
	chrono.stop(0);
	cout << "Chrono duration: " << chrono.duration(0) << endl;
	delete edmondsKarp;

	FordFulkerson* fordFulkersonDFS = new FordFulkersonDFS();
	chrono.start(1);
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
	Graph data(57);

	uint i = 4;

	while (cin >> origin)	// operacions descrites a la pagina 390 del llibre
	{
		cin >> destination;
		cin >> departureTime;
		cin >> arrivalTime;

		Vertex vorigin(origin, departureTime);
		Vertex vdestination(destination, arrivalTime);

		data.addEdge(vorigin, vdestination);

		i += 2;
	}

	version1(data);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(data);	// Eliminar els lower bound
	deleteDemand(data);		// Eliminar les demandes

	transformMax(data);

	data.updateMaxFlights(57);
	transformMax(data);
}
