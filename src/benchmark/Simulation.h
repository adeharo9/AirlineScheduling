#ifndef AIRLINESCHEDULING_SIMULATION_H
#define AIRLINESCHEDULING_SIMULATION_H


#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#include "../structures/Graph.h"
#include "../algorithms/Algorithm.h"
#include "../algorithms/EdmondsKarp.h"
#include "../algorithms/FordFulkersonDFS.h"
#include "../algorithms/DinicBlockingFlow.h"
#include "Mode.h"

using namespace std;

typedef vector<vector<int> > imatrix;

class Simulation
{
private:

	/* ATTRIBUTES */

	static const string V1_NAME;
	static const string V2_NAME;

	static const string DATA_DIR;
	static const string INSTANCE_NAME;
	static const string INSTANCE_SEPARATOR;
	static const string INSTANCE_EXTENSION;

	static const string OUTPUT_DIR;
	static const string OUTPUT_MANUAL_DIR;
	static const string OUTPUT_FILENAME;
	static const string OUTPUT_SEPARATOR;
	static const string OUTPUT_EXTENSION;

	static const string SIMULATIONS_DIR;
	static const string SIMULATIONS_FILENAME;
	static const string SIMULATIONS_SEPARATOR;
	static const string SIMULATIONS_EXTENSION;

	static const int MIN_TRANSITION_TIME = 15;

	Mode mode;
	string outputFilePath;
	string simulationsFilePath;

	string instanceName;

	ifstream inputFile;
	ofstream outputFile;
	ofstream simulationsFile;

	Graph originalBasicGraph;
	Graph originalCompleteGraph;
	Graph graph;
	bool firstIteration = true;
	bool needsInputGraph;

	Algorithm* algorithm;

	imatrix adjacenceMatrixGraph;
	imatrix adjacenceMatrixResidualGraph;

	int maxFlow;
	uint maxFlights;

public:

	/* CONSTRUCTORS */

	explicit Simulation(Mode inMode);

	/* GENERAL SIMULATION METHODS */

	void input();

	void manualInput();

	void load(uint index1, uint index2, uint index3);

	void setAlgorithm(Algorithm* inAlgorithm);

	void initialize();

	void run();

	void processResults();

	void end();

	void reset();

	void setMode(Mode inMode);

private:

	/* SPECIFIC SIMULATION METHODS */

	void version1();

	void version2();

	void deleteLowerBound();

	void deleteDemand();

	void transformMax();

	int dicotomic(uint low, uint high, bool lastIterationCalc);

	bool reachable(uint destination, uint origin);

	/* OUTPUT METHODS */

	void printSol(const vector<vector<int> > &residualGraph, const vector<vector<int> > &initialGraph);
};


#endif // AIRLINESCHEDULING_SIMULATION_H
