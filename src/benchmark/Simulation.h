#ifndef AIRLINESCHEDULING_SIMULATION_H
#define AIRLINESCHEDULING_SIMULATION_H


#include <iostream>
#include <fstream>
#include <string>

#include "../structures/Graph.h"
#include "../algorithms/Algorithm.h"

using namespace std;

typedef vector<vector<int> > imatrix;

class Simulation
{
private:

	/* ATTRIBUTES */

	static const string DATA_DIR;
	static const string INSTANCE_NAME;
	static const string INSTANCE_SEPARATOR;
	static const string INSTANCE_EXTENSION;

	static const string RESULTS_DIR;
	static const string RESULTS_V1_FILENAME;
	static const string RESULTS_V2_FILENAME;
	static const string RESULTS_EXTENSION;

	static const string RESULTS_V1_FILEPATH;
	static const string RESULTS_V2_FILEPATH;

	static const int MIN_TRANSITION_TIME = 15;

	string instanceName;

	ifstream instance;
	ofstream results;

	Graph graph;
	Algorithm* algorithm;

	imatrix adjacenceMatrixGraph;

	int maxFlow;
	uint maxFlights;

public:

	/* CONSTRUCTORS */

	Simulation() = default;

	/* GENERAL SIMULATION METHODS */

	void load(uint index1, uint index2, uint index3);

	void setAlgorithm(Algorithm* inAlgorithm);

	void initialize();

	void run();

	void end();

	void reset();

private:

	void input();

	/* SPECIFIC SIMULATION METHODS */

	void version1();

	void version2();

	void deleteLowerBound();

	void deleteDemand();

	void transformMax();

	int dicotomic(uint low, uint high);

	bool reachable(uint destination, uint origin);
};


#endif // AIRLINESCHEDULING_SIMULATION_H
