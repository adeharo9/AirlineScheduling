#ifndef AIRLINESCHEDULING_BENCHMARK_H
#define AIRLINESCHEDULING_BENCHMARK_H

#include "Simulation.h"
#include "../algorithms/EdmondsKarp.h"
#include "../utils/Chrono.h"

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

	Chrono chrono;

	Simulation simulation;

public:

	void initialize();

	void run();

	void runSingle(uint index1, uint index2, uint index3, Algorithm* algorithm);

	void saveResults(uint index1, uint index2, uint index3, ldouble duration);
};


#endif // AIRLINESCHEDULING_BENCHMARK_H
