#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Aresta
{
	int n;
	int lw; //lower bound
	int cap;//capacity

	Aresta() = default
	{

	}

	Aresta(int to, int c)
	{
		n=to;
		cap=c;
		lw=0;
	}
};

struct Node
{
	int ciutat;
	int hora;
	int demanda;

	Node() = default
	{

	}

	Node(int c, int h)
	{
		ciutat=c;
		hora=h;
		demanda=0;
	}
};

void printState(const vector<Node> &n, const vector<vector<Aresta>> &g)
{
	for(int i=0; i<n.size(); ++i)
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
				cout << endl << "Node " << i;

				if (i%2==0)
				{
					cout << " (Origen)";
				}
				else
				{
					cout << " (Destí)";
				}

				cout << " :" << endl;
				cout << "(Ciutat: " << n[i].ciutat << ",Hora: " << n[i].hora << ",Demanda: " << n[i].demanda << ")" << endl;
				break;
		}
		for (int j=0; j<g[i].size(); j++)
		{
			cout << "Aresta" << j << ":";
			cout << "(" << g[i][j].n << ", low: " << g[i][j].lw << ", cap: " << g[i][j].cap << " )" << endl;
		}
	}
}

/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void version1 (const vector<Node> & n, vector<vector<Aresta> > &g)
{
	for (int i = 5; i < n.size(); i += 2)	//i es desti
	{
		for (int j = 4; j < n.size(); j += 2)	//j es origen
		{
			if (i != j - 1)	//per evitar fer calculs sobre el mateix vol
			{
				if (n[i].ciutat == n[j].ciutat and n[j].hora - n[i].hora >= 15)
				{
					//aresta del desti i al origen j amb pes 1
					g[i].push_back(Aresta(j, 1));
				}
			}
		}
	}
}

int main()
{
	int o, d, h1, h2;
	//estructura de dades per guardar les arestes
	vector<vector<Aresta>> graf(4);//sources and sinks
	//graf [0] source without demands
	//graf [1] sink without demands
	//graf [2] source with demands
	//graf [3] sink with demands

	//nodes
	vector<Node> nodes(4);

	int i = 4;
	while (cin >> o >> d >> h1 >> h2)
	{
		//operacions descrites a la pagina 390 del llibre
		//afegeix el node de la ciutat d'origen
		nodes.push_back(Node(o, h1));
		//afegeix el node de la ciutat de destí
		nodes.push_back(Node(d, h2));
		//afegeix l'aresta entre vols
		graf.push_back(vector<Aresta>(1, Aresta(i + 1, 1)));
		graf[i][0].lw = 1;
		//afegeix l'aresta del source al origen
		graf[2].push_back(Aresta(i, 1));
		//afegeix l'aresta del desti al sink
		graf.push_back(vector<Aresta>(1, Aresta(3, 1)));
		i += 2;
	}

	//TODO Falta la aresta de s a t amb capacitat k

	version1(nodes, graf);
	printState(nodes, graf);
}
