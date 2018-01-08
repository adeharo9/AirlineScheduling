#ifndef AIRLINESCHEDULING_ALGORITHM_H
#define AIRLINESCHEDULING_ALGORITHM_H

#include <vector>

using namespace std;

typedef unsigned int uint;

class Algorithm
{
public:

	virtual int algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V) = 0;
};


#endif // AIRLINESCHEDULING_ALGORITHM_H
