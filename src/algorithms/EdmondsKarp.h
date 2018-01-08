#ifndef AIRLINESCHEDULING_EDMONDSKARP_H
#define AIRLINESCHEDULING_EDMONDSKARP_H

#include <climits>
#include <queue>
#include <vector>

#include "FordFulkerson.h"

using namespace std;

typedef unsigned int uint;

class EdmondsKarp : public FordFulkerson
{
public:
	static const string ID;

	/* GRAPH TRAVELING METHODS */

	bool travelGraph(const vector<vector<int> > &residualGraph, uint s, uint t, vector<uint> &parent, uint V) override;
};

#endif //AIRLINESCHEDULING_EDMONDSKARP_H
