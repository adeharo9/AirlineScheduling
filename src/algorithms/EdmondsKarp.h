#ifndef AIRLINESCHEDULING_EDMONDSKARP_H
#define AIRLINESCHEDULING_EDMONDSKARP_H

#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>

#include "FordFulkerson.h"

using namespace std;

typedef unsigned int uint;

// Traces back and prints the solution
class EdmondsKarp : public FordFulkerson
{
public:

	/* ALIASES OF BASE CLASS METHODS */

	int edmondsKarp(vector<vector<int>> &residualGraph, uint s, uint t, uint V);

	/* GRAPH TRAVELING METHODS */

	bool travelGraph(const vector<vector<int>> &residualGraph, uint s, uint t, vector<uint> &parent, uint V) override;

};

#endif //AIRLINESCHEDULING_EDMONDSKARP_H
