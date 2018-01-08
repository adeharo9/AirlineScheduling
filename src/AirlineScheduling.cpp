#include "benchmark/Benchmark.h"

void runModeBenchmark(Mode mode)
{
	Benchmark benchmark(mode);
	benchmark.initialize();

	switch (mode)
	{
		case MANUAL:
		case MANUAL_1:
		case MANUAL_2:
			benchmark.manualRun();
			break;

		default:
			benchmark.run();
			break;
	}
}

int main (int argc, char* argv[])
{
	if(argc == 1)
	{
		runModeBenchmark(MANUAL);
	}
	else if(string(argv[1]) == "ALL")
	{
		runModeBenchmark(VERSION_1_EK);
		runModeBenchmark(VERSION_1_FF_DFS);
		runModeBenchmark(VERSION_2_EK);
		runModeBenchmark(VERSION_2_FF_DFS);
	}
	else if(string(argv[1]) == "1")
	{
		if(argc == 2)
		{
			runModeBenchmark(MANUAL_1);
		}
		else if(string(argv[2]) == "ALL")
		{
			runModeBenchmark(VERSION_1_EK);
			runModeBenchmark(VERSION_1_FF_DFS);
		}
		else if(string(argv[2]) == "EK")
		{
			runModeBenchmark(VERSION_1_EK);
		}
		else if(string(argv[2]) == "FF-DFS")
		{
			runModeBenchmark(VERSION_1_FF_DFS);
		}
		else
		{
			runModeBenchmark(MANUAL_1);
		}
	}
	else if(string(argv[1]) == "2")
	{
		if(argc == 2)
		{
			runModeBenchmark(MANUAL_2);
		}
		else if(string(argv[2]) == "ALL")
		{
			runModeBenchmark(VERSION_2_EK);
			runModeBenchmark(VERSION_2_FF_DFS);
		}
		else if(string(argv[2]) == "EK")
		{
			runModeBenchmark(VERSION_2_EK);
		}
		else if(string(argv[2]) == "FF-DFS")
		{
			runModeBenchmark(VERSION_2_FF_DFS);
		}
		else
		{
			runModeBenchmark(MANUAL_2);
		}
	}
	else if(string(argv[1]) == "EK")
	{
		runModeBenchmark(VERSION_1_EK);
		runModeBenchmark(VERSION_2_EK);
	}
	else if(string(argv[1]) == "FF-DFS")
	{
		runModeBenchmark(VERSION_1_FF_DFS);
		runModeBenchmark(VERSION_2_FF_DFS);
	}
	else
	{
		runModeBenchmark(MANUAL);
	}
}
