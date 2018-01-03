#include <iostream>
#include <vector>
#include <map>

#include "utils/Constants.h"
#include "utils/Debug.h"
#include "utils/Utils.h"
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
	for (uint i = 5; i < n.size(); i += 2)	// i es desti
	{
		for (uint j = 4; j < n.size(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (n[i].city == n[j].city and n[j].time - n[i].time >= MIN_TRANSITION_TIME)
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
	uint origin;
	uint destination;
	uint departureTime;
	uint arrivalTime;

	// estructura de dades per guardar les arestes
	// graf [0] source without demands
	// graf [1] sink without demands
	// graf [2] source with demands
	// graf [3] sink with demands
	vector<vector<Aresta>> graf(MIN_NODES);// sources and sinks

	// nodes
	vector<Node> nodes(MIN_NODES);

	uint i = 4;

	while (cin >> origin >> destination >> departureTime >> arrivalTime)	// operacions descrites a la pagina 390 del llibre
	{
		nodes.emplace_back(Node(origin, departureTime));					// Afegeix el node de la ciutat d'origen
		nodes.emplace_back(Node(destination, arrivalTime));					// Afegeix el node de la ciutat de destí
		graf.emplace_back(vector<Aresta>(1, Aresta(i + 1, 1)));				// Afegeix l'aresta entre vols

		graf[i][0].lowerBound = 1;

		graf[2].emplace_back(Aresta(i, 1));									// Afegeix l'aresta del source al origen
		graf.emplace_back(vector<Aresta>(1, Aresta(3, 1)));					// Afegeix l'aresta del desti al sink

		i += 2;
	}

	// TODO Falta la aresta de s a t amb capacitat k

	version1(nodes, graf);
	Debug::printState(nodes, graf);
}
