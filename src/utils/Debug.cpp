#include "Debug.h"

void Debug::printState(const vector<Vertex>& n, const vector<vector<Edge>>& g)
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
				cout << "(Ciutat: " << n[i].city << ", Hora: " << n[i].time << ", Demanda: " << n[i].demand << ")" << endl;
				break;
		}
		for (int j = 0; j < g[i].size(); ++j)
		{
			cout << "Edge" << j << ": ";
			cout << "(" << g[i][j].n << ", low: " << g[i][j].lowerBound << ", capacity: " << g[i][j].capacity << " )" << endl;
		}
	}
}