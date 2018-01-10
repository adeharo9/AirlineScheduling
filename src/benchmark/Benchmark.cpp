#include "Benchmark.h"

const string Benchmark::V1_NAME = "1";
const string Benchmark::V2_NAME = "2";

const string Benchmark::INSTANCE_NAME = "instance";
const string Benchmark::INSTANCE_SEPARATOR = "_";
const string Benchmark::INSTANCE_EXTENSION = ".air";

const string Benchmark::OUTPUT_DIR = "./results/output/";
const string Benchmark::OUTPUT_MANUAL_DIR = "./";
const string Benchmark::OUTPUT_FILENAME = "Output";
const string Benchmark::OUTPUT_SEPARATOR = "_";
const string Benchmark::OUTPUT_EXTENSION = ".txt";

const string Benchmark::SIMULATIONS_DIR = "./results/simulations/";
const string Benchmark::SIMULATIONS_FILENAME = "Resultado";
const string Benchmark::SIMULATIONS_SEPARATOR = "_";
const string Benchmark::SIMULATIONS_EXTENSION = ".txt";

const string Benchmark::BENCHMARK_DIR = "./results/benchmark/";
const string Benchmark::BENCHMARK_FILENAME = "Benchmark";
const string Benchmark::BENCHMARK_SEPARATOR = "_";
const string Benchmark::BENCHMARK_EXTENSION = ".txt";

Benchmark::Benchmark(Mode inMode) : simulation(inMode)
{
	this -> setMode(inMode);
}

void Benchmark::initialize()
{
	ofstream outputFile;
	ofstream simulationsFile;
	ofstream benchmarkFile;

	outputFile.open(outputFilePath, fstream::trunc);
	outputFile.close();

	simulationsFile.open(simulationsFilePath, fstream::trunc);
	simulationsFile.close();

	benchmarkFile.open(benchmarkFilePath, fstream::trunc);
	benchmarkFile.close();
}

void Benchmark::manualRun()
{
	Algorithm* algorithm;

	EdmondsKarp edmondsKarp;
	FordFulkersonDFS fordFulkersonDFS;
	DinicBlockingFlow dinicBlockingFlow;

	switch (mode)
	{
		case VERSION_1_DI_MANUAL:
		case VERSION_2_DI_MANUAL:
			algorithm = &dinicBlockingFlow;
			break;

		case MANUAL_ALL:
		case MANUAL_1:
		case MANUAL_2:
		case VERSION_1_EK_MANUAL:
		case VERSION_2_EK_MANUAL:
			algorithm = &edmondsKarp;
			break;

		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			algorithm = &fordFulkersonDFS;
			break;

		default:
			throw invalid_argument("mode");
	}

	manualRunSingle(algorithm);
}

void Benchmark::run()
{
	Algorithm* algorithm;

	EdmondsKarp edmondsKarp;
	FordFulkersonDFS fordFulkersonDFS;
	DinicBlockingFlow dinicBlockingFlow;

	switch (mode)
	{
		case VERSION_1_DI_AUTO:
		case VERSION_2_DI_AUTO:
			algorithm = &dinicBlockingFlow;
			break;

		case VERSION_1_EK_AUTO:
		case VERSION_2_EK_AUTO:
			algorithm = &edmondsKarp;
			break;

		case VERSION_1_FF_DFS_AUTO:
		case VERSION_2_FF_DFS_AUTO:
			algorithm = &fordFulkersonDFS;
			break;

		default:
			throw invalid_argument("mode");
	}

	run(algorithm);
}

void Benchmark::run(Algorithm* algorithm)
{
	for (uint i = FILE_PARAMETER_1_FIRST; i <= FILE_PARAMETER_1_LAST; ++i)
	{
		for (uint j = FILE_PARAMETER_2_FIRST; j <= FILE_PARAMETER_2_LAST; ++j)
		{
			for (uint k = FILE_PARAMETER_3_FIRST; k <= FILE_PARAMETER_3_LAST; ++k)
			{
				runSingle(i, j, k, algorithm);
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

void Benchmark::manualRunSingle(Algorithm* algorithm)
{
	simulation.manualInput();
	simulation.setAlgorithm(algorithm);

	switch (mode)
	{
		case MANUAL_ALL:
			manualRunSingleMode(MANUAL_1);
			manualRunSingleMode(MANUAL_2);
			break;

		case MANUAL_1:
		case VERSION_1_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
			manualRunSingleMode(MANUAL_1);
			break;

		case MANUAL_2:
		case VERSION_2_DI_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			manualRunSingleMode(MANUAL_2);
			break;

		default:
			throw invalid_argument("mode");
	}
}

void Benchmark::manualRunSingleMode(Mode inMode)
{
	if(mode != inMode)
	{
		this -> setMode(inMode);
	}

	chrono.start(0);
	simulation.run();
	chrono.stop(0);

	simulation.end();

	chrono.reset(0);
}

void Benchmark::saveResults(uint index1, uint index2, uint index3, ldouble duration)
{
	ofstream benchmarkFile;

	string instanceName = INSTANCE_NAME + INSTANCE_SEPARATOR + to_string(index1) + INSTANCE_SEPARATOR + to_string(index2) + INSTANCE_SEPARATOR + to_string(index3) + INSTANCE_EXTENSION;

	benchmarkFile.open(benchmarkFilePath, fstream:: out | fstream::app);

	benchmarkFile << instanceName << " " << "\t" << duration << endl;

	benchmarkFile.close();
}

void Benchmark::setMode(Mode inMode)
{
	string versionName;
	string idOutput;
	string idSimulations;
	string idBenchmark;

	this -> mode = inMode;
	this -> simulation.setMode(inMode);

	switch (inMode)
	{
		case MANUAL_ALL:
		case MANUAL_1:
		case VERSION_1_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_1_DI_AUTO:
		case VERSION_1_EK_AUTO:
		case VERSION_1_FF_DFS_AUTO:
			versionName = V1_NAME;
			break;

		case MANUAL_2:
		case VERSION_2_DI_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
		case VERSION_2_DI_AUTO:
		case VERSION_2_EK_AUTO:
		case VERSION_2_FF_DFS_AUTO:
			versionName = V2_NAME;
			break;

		default:
			throw invalid_argument("mode");
	}

	switch (mode)
	{
		case MANUAL_ALL:
		case MANUAL_1:
		case MANUAL_2:
		case VERSION_1_DI_MANUAL:
		case VERSION_2_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			idOutput = "";
			idSimulations = "";
			idBenchmark = "";
			break;

		case VERSION_1_DI_AUTO:
		case VERSION_2_DI_AUTO:
			idOutput = OUTPUT_SEPARATOR + DinicBlockingFlow::ID;
			idSimulations = SIMULATIONS_SEPARATOR + DinicBlockingFlow::ID;
			idBenchmark = SIMULATIONS_SEPARATOR + DinicBlockingFlow::ID;
			break;

		case VERSION_1_EK_AUTO:
		case VERSION_2_EK_AUTO:
			idOutput = OUTPUT_SEPARATOR + EdmondsKarp::ID;
			idSimulations = SIMULATIONS_SEPARATOR + EdmondsKarp::ID;
			idBenchmark = SIMULATIONS_SEPARATOR + EdmondsKarp::ID;
			break;

		case VERSION_1_FF_DFS_AUTO:
		case VERSION_2_FF_DFS_AUTO:
			idOutput = OUTPUT_SEPARATOR + FordFulkersonDFS::ID;
			idSimulations = SIMULATIONS_SEPARATOR + FordFulkersonDFS::ID;
			idBenchmark = SIMULATIONS_SEPARATOR + FordFulkersonDFS::ID;
			break;

		default:
			throw invalid_argument("mode");
	}

	outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + versionName + idOutput + OUTPUT_EXTENSION;
	simulationsFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + versionName + idSimulations + SIMULATIONS_EXTENSION;
	benchmarkFilePath = BENCHMARK_DIR + BENCHMARK_FILENAME + versionName + idBenchmark + BENCHMARK_EXTENSION;
}