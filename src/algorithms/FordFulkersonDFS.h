#ifndef AIRLINESCHEDULING_FORDFULKERSONDFS_H
#define AIRLINESCHEDULING_FORDFULKERSONDFS_H

#include <iostream>
#include <climits>
#include <cstring>
#include <stack>
#include <vector>

#include "FordFulkerson.h"

class FordFulkersonDFS : public FordFulkerson
{

	/* ALIASES OF BASE CLASS METHODS */

	int fordFulkersonDFS(vector<vector<int>> &residualGraph, uint s, uint t, uint V);

	/* GRAPH TRAVELING METHODS */

	bool travelGraph(const vector<vector<int>> &residualGraph, uint s, uint t, vector<uint> &parent, uint V) override;
};


#endif //AIRLINESCHEDULING_FORDFULKERSONDFS_H
