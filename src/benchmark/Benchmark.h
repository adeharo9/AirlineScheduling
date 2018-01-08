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

	static const string V1_NAME;
	static const string V2_NAME;

	static const string INSTANCE_NAME;
	static const string INSTANCE_SEPARATOR;
	static const string INSTANCE_EXTENSION;

	static const string OUTPUT_DIR;
	static const string OUTPUT_FILENAME;
	static const string OUTPUT_SEPARATOR;
	static const string OUTPUT_EXTENSION;

	static const string SIMULATIONS_DIR;
	static const string SIMULATIONS_FILENAME;
	static const string SIMULATIONS_SEPARATOR;
	static const string SIMULATIONS_EXTENSION;

	static const string BENCHMARK_DIR;
	static const string BENCHMARK_FILENAME;
	static const string BENCHMARK_SEPARATOR;
	static const string BENCHMARK_EXTENSION;

	static const uint FILE_PARAMETER_1_FIRST = 100;
	static const uint FILE_PARAMETER_1_LAST = 100;

	static const uint FILE_PARAMETER_2_FIRST = 2;
	static const uint FILE_PARAMETER_2_LAST = 30;

	static const uint FILE_PARAMETER_3_FIRST = 1;
	static const uint FILE_PARAMETER_3_LAST = 10;

	const Mode mode;
	string outputFilePath;
	string simulationsFilePath;
	string benchmarkFilePath;

	Chrono chrono;

	Simulation simulation;

public:

	explicit Benchmark(Mode inMode);

	void initialize();

	void run();

	void run(Algorithm* algorithm);

	void runSingle(uint index1, uint index2, uint index3, Algorithm* algorithm);

	void saveResults(uint index1, uint index2, uint index3, ldouble duration);
};


#endif // AIRLINESCHEDULING_BENCHMARK_H
