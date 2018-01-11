#ifndef AIRLINESCHEDULING_DINICBLOCKINGFLOW_H
#define AIRLINESCHEDULING_DINICBLOCKINGFLOW_H


#include "Algorithm.h"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

typedef unsigned int uint;

class DinicBlockingFlow : public Algorithm
{
private:

	bool buildLevelGraph(uint s, uint t, vector<vector<int> > &residualGraph, vector<int> &levels);

	int blockingFlow(uint u, int flow, uint t, vector<int> &lastAdjacent, vector<vector<int> > &residualGraph, vector<int> &levels);

public:

	static const string ID;

	int algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V) override;
};


#endif // AIRLINESCHEDULING_DINICBLOCKINGFLOW_H
