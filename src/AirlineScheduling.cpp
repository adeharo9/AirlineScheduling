#include "benchmark/Benchmark.h"

void runModeBenchmark(Mode mode)
{
	Benchmark benchmark1(mode);
	benchmark1.initialize();
	benchmark1.run();
}

int main (int argc, char* argv[])
{
	EdmondsKarp edmondsKarp;


	if(argc == 1)
	{
		runModeBenchmark(VERSION_1_ALL);
		runModeBenchmark(VERSION_2_ALL);
	}
	else
	{
		if(string(argv[1]) == "1")
		{
			if(string(argv[2]) == "EK")
			{
				runModeBenchmark(VERSION_1_EK);
			}
			else if(string(argv[2]) == "FF_DFS")
			{
				runModeBenchmark(VERSION_1_FF_DFS);
			}
			else
			{
				runModeBenchmark(VERSION_1_ALL);
			}
		}
		else if(string(argv[1]) == "2")
		{
			if(string(argv[2]) == "EK")
			{
				runModeBenchmark(VERSION_2_EK);
			}
			else if(string(argv[2]) == "FF_DFS")
			{
				runModeBenchmark(VERSION_2_FF_DFS);
			}
			else
			{
				runModeBenchmark(VERSION_2_ALL);
			}
		}
		else if(string(argv[1]) == "EK")
		{
			runModeBenchmark(VERSION_1_EK);
			runModeBenchmark(VERSION_2_EK);
		}
		else if(string(argv[1]) == "FF_DFS")
		{
			runModeBenchmark(VERSION_1_FF_DFS);
			runModeBenchmark(VERSION_2_FF_DFS);
		}
	}
}
