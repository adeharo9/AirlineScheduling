#include "Benchmark.h"

const string Benchmark::INSTANCE_NAME = "instance";
const string Benchmark::INSTANCE_SEPARATOR = "_";
const string Benchmark::INSTANCE_EXTENSION = ".air";

const string Benchmark::RESULTS_DIR = "./results/simulations/";
const string Benchmark::RESULTS_V1_FILENAME = "Resultado1";
const string Benchmark::RESULTS_V2_FILENAME = "Resultado2";
const string Benchmark::RESULTS_EXTENSION = ".txt";

const string Benchmark::RESULTS_V1_FILEPATH = RESULTS_DIR + RESULTS_V1_FILENAME + RESULTS_EXTENSION;
const string Benchmark::RESULTS_V2_FILEPATH = RESULTS_DIR + RESULTS_V2_FILENAME + RESULTS_EXTENSION;

const string Benchmark::BENCHMARK_RESULTS_DIR = "./results/benchmark/";
const string Benchmark::BENCHMARK_RESULTS_V1_FILENAME = "Benchmark1";
const string Benchmark::BENCHMARK_RESULTS_V2_FILENAME = "Benchmark2";
const string Benchmark::BENCHMARK_RESULTS_EXTENSION = ".txt";

const string Benchmark::BENCHMARK_V1_FILEPATH = BENCHMARK_RESULTS_DIR + BENCHMARK_RESULTS_V1_FILENAME + BENCHMARK_RESULTS_EXTENSION;
const string Benchmark::BENCHMARK_V2_FILEPATH = BENCHMARK_RESULTS_DIR + BENCHMARK_RESULTS_V2_FILENAME + BENCHMARK_RESULTS_EXTENSION;

void Benchmark::initialize()
{
	ofstream simulationResults;
	ofstream benchmarkResults;

	simulationResults.open(RESULTS_V1_FILEPATH, fstream::trunc);
	simulationResults.close();

	simulationResults.open(RESULTS_V2_FILEPATH, fstream::trunc);
	simulationResults.close();

	benchmarkResults.open(BENCHMARK_V1_FILEPATH, fstream::trunc);
	benchmarkResults.close();

	benchmarkResults.open(BENCHMARK_V2_FILEPATH, fstream::trunc);
	benchmarkResults.close();
}

void Benchmark::run()
{
	EdmondsKarp edmondsKarp;

	for(uint i = FIRST_FILE_PARAMETER_1; i <= LAST_FILE_PARAMETER_1; ++i)
	{
		for (uint j = FIRST_FILE_PARAMETER_2; j <= LAST_FILE_PARAMETER_2; ++j)
		{
			for (uint k = FIRST_FILE_PARAMETER_3; k <= LAST_FILE_PARAMETER_3; ++k)
			{
				runSingle(i, j, k, &edmondsKarp);
			}
		}
	}
}

void Benchmark::runSingle(uint index1, uint index2, uint index3, Algorithm* algorithm)
{
	simulation.load(index1, index2, index3);
	simulation.setAlgorithm(algorithm);

	chrono.start(0);
	simulation.run();
	chrono.stop(0);
	saveResults(index1, index2, index3, chrono.duration(0));

	simulation.end();
	simulation.reset();

	chrono.reset(0);
}

void Benchmark::saveResults(uint index1, uint index2, uint index3, ldouble duration)
{
	ofstream benchmarkResults;

	string instanceName = INSTANCE_NAME + INSTANCE_SEPARATOR + to_string(index1) + INSTANCE_SEPARATOR + to_string(index2) + INSTANCE_SEPARATOR + to_string(index3) + INSTANCE_EXTENSION;

	benchmarkResults.open(BENCHMARK_V1_FILEPATH, fstream:: out | fstream::app);

	benchmarkResults << instanceName << " " << "\t" << duration << endl;

	benchmarkResults.close();
}