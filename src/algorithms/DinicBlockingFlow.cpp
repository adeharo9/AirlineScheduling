#include "DinicBlockingFlow.h"

const string DinicBlockingFlow::ID = "DI";

int DinicBlockingFlow::algorithm(vector<vector<int> > &graph, vector<vector<int> > &residualGraph, uint s, uint t, uint V)
{
	graph = vector<vector<int> >();
	residualGraph = vector<vector<int> >();
	s = 0;
	t = 0;
	V = 0;

	return s + t + V;
}