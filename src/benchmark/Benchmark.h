#ifndef AIRLINESCHEDULING_BENCHMARK_H
#define AIRLINESCHEDULING_BENCHMARK_H


#include "Simulation.h"
#include "../algorithms/EdmondsKarp.h"
#include "../utils/Chrono.h"

class Benchmark
{
private:

	/* ATTRIBUTES */

	static const uint FIRST_FILE_PARAMETER_1 = 100;
	static const uint LAST_FILE_PARAMETER_1 = 100;

	static const uint FIRST_FILE_PARAMETER_2 = 2;
	static const uint LAST_FILE_PARAMETER_2 = 30;

	static const uint FIRST_FILE_PARAMETER_3 = 1;
	static const uint LAST_FILE_PARAMETER_3 = 10;

	Chrono chrono;

	Simulation simulation;

public:

	void run();

	void runSingle(uint index1, uint index2, uint index3, Algorithm* algorithm);
};


#endif // AIRLINESCHEDULING_BENCHMARK_H
