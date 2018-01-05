#include <iostream>
#include <vector>

#include "algorithms/EdmondsKarp.h"
#include "utils/Chrono.h"
#include "utils/Constants.h"
#include "utils/Debug.h"
#include "utils/Utils.h"
#include "structures/Edge.h"
#include "structures/Vertex.h"
#include "algorithms/FordFulkersonDFS.h"

using namespace std;

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void version1 (const vector<Vertex>& nodes, vector<vector<Edge>>& graph)
{
	for (uint i = 5; i < nodes.size(); i += 2)	// i es desti
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
					graph[i].emplace_back(Edge(j, 1));
				}
			}
		}
	}
}
/*
  elimina els lower bound de les arestes i actualitza les demandes
  les uniques arestes amb lower suerten de les ciutats d'origen
*/
void deleteLowerBound(vector<Vertex> &n, vector<vector<Edge>> &g)
{
	for (uint i = 4; i < n.size(); i += 2)
	{
		//la primera aresta es la del viatge
		g[i][0].setCapacity(g[i][0].getCapacity() - g[i][0].getLowerBound());
		g[i][0].setLowerBound(0);

		//sumo 1 a la demanda de l'origen, i resto 1 a la de destí
		n[i].incrementDemand();
		n[i + 1].decrementDemand();
	}
}

/*
  elimina les demandes  i actualizta el sink i drain reals amb les
  arestes necessaries
*/
void deleteDemand(vector<Vertex> &nodes, vector<vector<Edge>> &graph)
{
	for (uint i = 2; i < nodes.size(); ++i)
	{
		if (nodes[i].getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			graph[i].emplace_back(Edge(1, nodes[i].getDemand()));
			nodes[i].setDemand(0);
		}
		else if (nodes[i].getDemand() < 0)	// Si es source s va a el
		{
			graph[0].emplace_back(Edge(i, -nodes[i].getDemand()));
			nodes[i].setDemand(0);
		}
	}
}

void transformMax(vector<Vertex> &n, vector<vector<Edge>> &g)
{
	vector<vector<int>> graph(n.size(), vector<int>(n.size(), 0));

	for(uint i = 0; i < n.size(); ++i)
	{
		for (uint j = 0; j < g[i].size(); ++j)
		{
			graph[i][g[i][j].getDestination()] = g[i][j].getCapacity();
		}
	}

	cout << "Max Flow: " << endl;

	FordFulkerson* edmondsKarp = new EdmondsKarp();

	Chrono chrono;

	chrono.start(0);

	cout << endl << edmondsKarp -> algorithm(graph, 0, 1, n.size()) << endl;

	chrono.stop(0);

	cout << "Chrono duration: " << chrono.duration(0) << endl;

	delete edmondsKarp;


	FordFulkerson* fordFulkersonDFS = new FordFulkersonDFS();

	chrono.start(1);

	cout << endl << fordFulkersonDFS -> algorithm(graph, 0, 1, n.size()) << endl;

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
	vector<vector<Edge>> graph(MIN_VERTICES);	// sources and sinks
	vector<Vertex> nodes(MIN_VERTICES);			// nodes

	uint i = 4;

	while (cin >> origin)	// operacions descrites a la pagina 390 del llibre
	{
		cin >> destination;
		cin >> departureTime;
		cin >> arrivalTime;

		nodes.emplace_back(Vertex(origin, departureTime));		// Afegeix el node de la ciutat d'origen
		nodes.emplace_back(Vertex(destination, arrivalTime));	// Afegeix el node de la ciutat de destí

		graph.emplace_back(vector<Edge>(1, Edge(i + 1, 1, 1)));		// Afegeix l'aresta entre vols

		graph[2].emplace_back(Edge(i, 1));						// Afegeix l'aresta del source al origen
		graph.emplace_back(vector<Edge>(1, Edge(3, 1)));			// Afegeix l'aresta del desti al sink

		i += 2;
	}

	int k = 2;

	graph[2].emplace_back(Edge(3, k));
	nodes[2].setDemand(-k);
	nodes[3].setDemand(k);

	version1(nodes, graph);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(nodes, graph);	// Eliminar els lower bound
	deleteDemand(nodes, graph);		// Eliminar les demandes


	transformMax(nodes, graph);
	Debug::printState(nodes, graph);
}
