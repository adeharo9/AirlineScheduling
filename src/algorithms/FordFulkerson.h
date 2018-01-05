#ifndef AIRLINESCHEDULING_FORDFULKERSON_H
#define AIRLINESCHEDULING_FORDFULKERSON_H

#include <iostream>
#include <climits>
#include <cstring>
#include <vector>

#include "Algorithm.h"

typedef unsigned int uint;

using namespace std;

class FordFulkerson : public Algorithm
{
public:
	/* CONSTRUCTORS */

	FordFulkerson() = default;

	/* GRAPH TRAVELING METHODS */

	virtual bool travelGraph(const vector<vector<int>> &rGraph , uint s, uint t, vector<uint> &parent, uint V) = 0;

	/* BASE ALGORITHM */

	int algorithm(vector<vector<int>> &graph, uint s, uint t, uint V);

	/* OUTPUT METHODS */

	void print_sol(const vector<vector<int>> &g, const vector<vector<int>> &ini);

};


#endif //AIRLINESCHEDULING_FORDFULKERSON_H
