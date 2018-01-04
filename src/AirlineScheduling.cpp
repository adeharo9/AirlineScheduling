#include <iostream>
#include <vector>

#include "algorithms/EdmondsKarp.h"
#include "utils/Chrono.h"
#include "utils/Constants.h"
#include "utils/Debug.h"
#include "utils/Utils.h"
#include "structures/Edge.h"
#include "structures/Vertex.h"

using namespace std;

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void version1 (const vector<Vertex>& n, vector<vector<Edge>>& g)
{
	for (uint i = 5; i < n.size(); i += 2)	// i es desti
	{
		for (uint j = 4; j < n.size(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (n[i].getCity() == n[j].getCity() and int(n[j].getTime()) - int(n[i].getTime()) >= MIN_TRANSITION_TIME)
				{
					if (i==7 and j==4){
						cout<<"Aqui estoy, con tiempo: "<<n[j].getTime() - n[i].getTime() <<" "<< MIN_TRANSITION_TIME<<endl;
					cout<<"n j "<<n[j].getTime()<<" n i "<< n[i].getTime()<<endl;
				}
					// aresta del desti i al origen j amb pes 1
					g[i].emplace_back(Edge(j, 1));
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
void deleteDemand(vector<Vertex> &n, vector<vector<Edge>> &g)
{
	for (uint i = 2; i < n.size(); ++i)
	{
		if (n[i].getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			g[i].emplace_back(Edge(1, n[i].getDemand()));
			n[i].setDemand(0);
		}
		else if (n[i].getDemand() < 0)	// Si es source s va a el
		{
			g[0].emplace_back(Edge(i, -n[i].getDemand()));
			n[i].setDemand(0);
		}
	}
}

void transformMax(vector<Vertex> &n, vector<vector<Edge>> &g)
{
	uint size = n.size();

	vector<vector<int>> gr (size,vector<int>(size,0));

	for(uint i = 0; i <size; ++i)
	{
		for (uint j = 0; j < g[i].size(); ++j)
		{
			gr[i][g[i][j].getN()] = g[i][j].getCapacity();
		}
	}

	cout << "Max Flow: " << endl;

	Chrono chrono;

	chrono.start(0);

	cout << endl << edmondsKarp(gr, 0, 1, size) << endl;

	chrono.stop(0);

	cout << "Chrono duration: " << chrono.duration(0) << endl;
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
	vector<vector<Edge>> graf(MIN_VERTICES);	// sources and sinks
	vector<Vertex> nodes(MIN_VERTICES);			// nodes

	uint i = 4;

	while (cin >> origin)	// operacions descrites a la pagina 390 del llibre
	{
		cin >> destination;
		cin >> departureTime;
		cin >> arrivalTime;

		nodes.emplace_back(Vertex(origin, departureTime));		// Afegeix el node de la ciutat d'origen
		nodes.emplace_back(Vertex(destination, arrivalTime));	// Afegeix el node de la ciutat de destí

		graf.emplace_back(vector<Edge>(1, Edge(i + 1, 1)));		// Afegeix l'aresta entre vols

		graf[i][0].setLowerBound(1);

		graf[2].emplace_back(Edge(i, 1));						// Afegeix l'aresta del source al origen
		graf.emplace_back(vector<Edge>(1, Edge(3, 1)));			// Afegeix l'aresta del desti al sink

		i += 2;
	}

	int k = 2;

	graf[2].emplace_back(Edge(3, k));
	nodes[2].setDemand(-k);
	nodes[3].setDemand(k);

	version1(nodes, graf);			// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound(nodes, graf);	// Eliminar els lower bound
	deleteDemand(nodes, graf);		// Eliminar les demandes


	Debug::printState(nodes, graf);
	transformMax(nodes, graf);
}
