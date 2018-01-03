#include <iostream>
#include <vector>
#include <map>

#include "utils/Constants.h"
#include "utils/Debug.h"
#include "structures/Aresta.h"
#include "structures/Node.h"

using namespace std;

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void version1 (const vector<Node>& n, vector<vector<Aresta>>& g)
{
	for (int i = 5; i < n.size(); i += 2)	// i es desti
	{
		for (int j = 4; j < n.size(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (n[i].city == n[j].city and n[j].time - n[i].time >= 15)
				{
					// aresta del desti i al origen j amb pes 1
					g[i].emplace_back(Aresta(j, 1));
				}
			}
		}
	}
}

int main()
{
	int origin, destination, departureTime, arrivalTime;
	// estructura de dades per guardar les arestes
	vector<vector<Aresta>> graf(MIN_NODES);// sources and sinks
	// graf [0] source without demands
	// graf [1] sink without demands
	// graf [2] source with demands
	// graf [3] sink with demands

	// nodes
	vector<Node> nodes(MIN_NODES);

	int i = 4;
	while (cin >> origin >> destination >> departureTime >> arrivalTime)
	{
		// operacions descrites a la pagina 390 del llibre
		// afegeix el node de la ciutat d'origen
		nodes.emplace_back(Node(origin, departureTime));
		// afegeix el node de la ciutat de destí
		nodes.emplace_back(Node(destination, arrivalTime));
		// afegeix l'aresta entre vols
		graf.emplace_back(vector<Aresta>(1, Aresta(i + 1, 1)));
		graf[i][0].lowerBound = 1;
		// afegeix l'aresta del source al origen
		graf[2].emplace_back(Aresta(i, 1));
		// afegeix l'aresta del desti al sink
		graf.emplace_back(vector<Aresta>(1, Aresta(3, 1)));
		i += 2;
	}

	// TODO Falta la aresta de s a t amb capacitat k

	version1(nodes, graf);
	Debug::printState(nodes, graf);
}
