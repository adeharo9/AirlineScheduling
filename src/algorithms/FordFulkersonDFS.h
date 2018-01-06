#ifndef AIRLINESCHEDULING_FORDFULKERSONDFS_H
#define AIRLINESCHEDULING_FORDFULKERSONDFS_H


#include <climits>
#include <stack>
#include <vector>

#include "FordFulkerson.h"

using namespace std;

class FordFulkersonDFS : public FordFulkerson
{

	/* ALIASES OF BASE CLASS METHODS */

	int fordFulkersonDFS(vector<vector<int>> &residualGraph, uint s, uint t, uint V);

	/* GRAPH TRAVELING METHODS */

	bool travelGraph(const vector<vector<int>> &residualGraph, uint s, uint t, vector<uint> &parent, uint V) override;
};


#endif // AIRLINESCHEDULING_FORDFULKERSONDFS_H
