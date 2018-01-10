#ifndef AIRLINESCHEDULING_DINICBLOCKINGFLOW_H
#define AIRLINESCHEDULING_DINICBLOCKINGFLOW_H


#include "Algorithm.h"
#include <vector>
#include <string>

using namespace std;

typedef unsigned int uint;

class DinicBlockingFlow : public Algorithm
{
public:

	static const string ID;

	int algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V) override;
};


#endif // AIRLINESCHEDULING_DINICBLOCKINGFLOW_H
