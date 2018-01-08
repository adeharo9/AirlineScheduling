#ifndef AIRLINESCHEDULING_BENCHMARK_H
#define AIRLINESCHEDULING_BENCHMARK_H


#include <string>

#include "Simulation.h"
#include "../algorithms/EdmondsKarp.h"
#include "../algorithms/FordFulkersonDFS.h"
#include "../utils/Chrono.h"
#include "Mode.h"

using namespace std;

class Benchmark
{
private:

	/* ATTRIBUTES */

	static const string INSTANCE_NAME;
	static const string INSTANCE_SEPARATOR;
	static const string INSTANCE_EXTENSION;

	static const string RESULTS_DIR;
	static const string RESULTS_V1_FILENAME;
	static const string RESULTS_V2_FILENAME;
	static const string RESULTS_EXTENSION;

	static const string RESULTS_V1_FILEPATH;
	static const string RESULTS_V2_FILEPATH;

	static const string BENCHMARK_RESULTS_DIR;
	static const string BENCHMARK_RESULTS_V1_FILENAME;
	static const string BENCHMARK_RESULTS_V2_FILENAME;
	static const string BENCHMARK_RESULTS_EXTENSION;

	static const string BENCHMARK_V1_FILEPATH;
	static const string BENCHMARK_V2_FILEPATH;

	static const uint FIRST_FILE_PARAMETER_1 = 100;
	static const uint LAST_FILE_PARAMETER_1 = 100;

	static const uint FIRST_FILE_PARAMETER_2 = 2;
	static const uint LAST_FILE_PARAMETER_2 = 30;

	static const uint FIRST_FILE_PARAMETER_3 = 1;
	static const uint LAST_FILE_PARAMETER_3 = 10;

	const Mode mode;

	Chrono chrono;

	Simulation simulation;

public:

	explicit Benchmark(Mode inMode);

	void initialize();

	void run();
	void run(vector<Algorithm*> algorithms);

	void runSingle(uint index1, uint index2, uint index3, Algorithm* algorithm);

	void saveResults(uint index1, uint index2, uint index3, ldouble duration);
};


#endif // AIRLINESCHEDULING_BENCHMARK_H
