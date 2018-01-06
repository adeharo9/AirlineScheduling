#include "Benchmark.h"

const string Benchmark::RESULTS_DIR = "./results/";
const string Benchmark::RESULTS_V1_FILENAME = "Resultado1";
const string Benchmark::RESULTS_V2_FILENAME = "Resultado2";
const string Benchmark::RESULTS_EXTENSION = ".txt";

const string Benchmark::RESULTS_V1_FILEPATH = RESULTS_DIR + RESULTS_V1_FILENAME + RESULTS_EXTENSION;
const string Benchmark::RESULTS_V2_FILEPATH = RESULTS_DIR + RESULTS_V2_FILENAME + RESULTS_EXTENSION;

void Benchmark::initialize()
{
	ofstream results;

	results.open(RESULTS_V1_FILEPATH, fstream::trunc);
	results.close();

	results.open(RESULTS_V2_FILEPATH, fstream::trunc);
	results.close();
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
	//simulation.initialize();

	chrono.start(0);
	simulation.run();
	chrono.stop(0);
    cout<<"Duration: "<<chrono.duration(0)<<endl;

	simulation.end();
	simulation.reset();

	chrono.reset(0);
}