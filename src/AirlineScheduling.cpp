#include <iostream>
#include "benchmark/Benchmark.h"

using namespace std;

void runModeBenchmark(Mode mode)
{
	Benchmark benchmark(mode);
	benchmark.initialize();

	switch (mode)
	{
		case MANUAL_ALL:
		case MANUAL_1:
		case MANUAL_2:
		case VERSION_1_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_2_DI_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			benchmark.manualRun();
			break;

		default:
			benchmark.run();
			break;
	}
}

void usage(char* argv[])
{
	cout << endl;
	cout << argv[0] << " [-12Lh] [-a algorithm] [-AM]" << endl << endl;
	cout << "OPTIONS: " << endl;
	cout << "	-1:" << endl;
	cout << "		Executes selected algorithms with version 1 of the problem." << endl;
	cout << "	-2:" << endl;
	cout << "		Executes selected algorithms with version 2 of the problem." << endl;
	cout << "	-L, --ALL:" << endl;
	cout << "		Executes selected algorithms in all versions of the problem." << endl << endl;
	cout << "	-h, --help:" << endl;
	cout << "		Show this help message." << endl << endl;
	cout << "	-a, --algorithm value:" << endl;
	cout << "		VALUE: " << endl;
	cout << "			ALL: Executes all algorithms secuentially." << endl;
	cout << "			DI: Dinic's blocking flow algorithm." << endl;
	cout << "			EK: Edmonds-Karp algorithm." << endl;
	cout << "			FF: FordFulkerson algorithm with DFS." << endl << endl;
	cout << "	-A, --auto:" << endl;
	cout << "		Uses automated input when combined with other options." << endl;
	cout << "	-M, --manual:" << endl;
	cout << "		Uses manual input when combined with other options." << endl << endl;

	exit(-1);
}

void executeMode(uint version, const string& algorithm, bool manual)
{
	if(version == 0 and algorithm == "ALL" and manual)
	{
		runModeBenchmark(MANUAL_ALL);
	}
	else if(version == 0 and algorithm == "ALL" and not manual)
	{
		runModeBenchmark(VERSION_1_DI_AUTO);
		runModeBenchmark(VERSION_1_EK_AUTO);
		runModeBenchmark(VERSION_1_FF_DFS_AUTO);
		runModeBenchmark(VERSION_2_DI_AUTO);
		runModeBenchmark(VERSION_2_EK_AUTO);
		runModeBenchmark(VERSION_2_FF_DFS_AUTO);
	}
	else if(version == 0 and algorithm == "DI" and manual)
	{

	}
	else if(version == 0 and algorithm == "DI" and not manual)
	{
		runModeBenchmark(VERSION_1_DI_AUTO);
		runModeBenchmark(VERSION_2_DI_AUTO);
	}
	else if(version == 0 and algorithm == "EK" and manual)
	{

	}
	else if(version == 0 and algorithm == "EK" and not manual)
	{
		runModeBenchmark(VERSION_1_EK_AUTO);
		runModeBenchmark(VERSION_2_EK_AUTO);
	}
	else if(version == 0 and algorithm == "FF" and manual)
	{

	}
	else if(version == 0 and algorithm == "FF" and not manual)
	{
		runModeBenchmark(VERSION_1_FF_DFS_AUTO);
		runModeBenchmark(VERSION_2_FF_DFS_AUTO);
	}
	else if(version == 1 and algorithm == "ALL" and manual)
	{
		runModeBenchmark(MANUAL_1);
	}
	else if(version == 1 and algorithm == "ALL" and not manual)
	{
		runModeBenchmark(VERSION_1_DI_AUTO);
		runModeBenchmark(VERSION_1_EK_AUTO);
		runModeBenchmark(VERSION_1_FF_DFS_AUTO);
	}
	else if(version == 1 and algorithm == "DI" and manual)
	{
		runModeBenchmark(VERSION_1_DI_MANUAL);
	}
	else if(version == 1 and algorithm == "DI" and not manual)
	{
		runModeBenchmark(VERSION_1_DI_AUTO);
	}
	else if(version == 1 and algorithm == "EK" and manual)
	{
		runModeBenchmark(VERSION_1_EK_MANUAL);
	}
	else if(version == 1 and algorithm == "EK" and not manual)
	{
		runModeBenchmark(VERSION_1_EK_AUTO);
	}
	else if(version == 1 and algorithm == "FF" and manual)
	{
		runModeBenchmark(VERSION_1_FF_DFS_MANUAL);
	}
	else if(version == 1 and algorithm == "FF" and not manual)
	{
		runModeBenchmark(VERSION_1_FF_DFS_AUTO);
	}
	else if(version == 2 and algorithm == "ALL" and manual)
	{
		runModeBenchmark(MANUAL_2);
	}
	else if(version == 2 and algorithm == "ALL" and not manual)
	{
		runModeBenchmark(VERSION_2_DI_AUTO);
		runModeBenchmark(VERSION_2_EK_AUTO);
		runModeBenchmark(VERSION_2_FF_DFS_AUTO);
	}
	else if(version == 2 and algorithm == "DI" and manual)
	{
		runModeBenchmark(VERSION_1_DI_MANUAL);
	}
	else if(version == 2 and algorithm == "DI" and not manual)
	{
		runModeBenchmark(VERSION_2_DI_AUTO);
	}
	else if(version == 2 and algorithm == "EK" and manual)
	{
		runModeBenchmark(VERSION_1_EK_MANUAL);
	}
	else if(version == 2 and algorithm == "EK" and not manual)
	{
		runModeBenchmark(VERSION_2_EK_AUTO);
	}
	else if(version == 2 and algorithm == "FF" and manual)
	{
		runModeBenchmark(VERSION_1_FF_DFS_MANUAL);
	}
	else if(version == 2 and algorithm == "FF" and not manual)
	{
		runModeBenchmark(VERSION_2_FF_DFS_AUTO);
	}
}

int main (int argc, char* argv[])
{
	uint version = 1;
	string algorithm = "EK";
	bool manual = true;

	if(argc == 1)
	{
		usage(argv);
	}
	else if(string(argv[1]) == "-L" or string(argv[1]) == "--ALL")
	{
		version = 0;
	}
	else if(string(argv[1]) == "-1")
	{
		version = 1;
	}
	else if(string(argv[1]) == "-2")
	{
		version = 2;
	}
	else if(string(argv[1]) == "-h" or string(argv[1]) == "--help")
	{
		usage(argv);
	}
	else
	{
		usage(argv);
	}

	if(argc == 2)
	{
		usage(argv);
	}
	else if(string(argv[2]) == "-a" or string(argv[2]) == "--algorithm")
	{
		if(argc == 3)
		{
			usage(argv);
		}
		else if(string(argv[3]) == "ALL")
		{
			algorithm = argv[3];
		}
		else if(string(argv[3]) == "DI")
		{
			algorithm = argv[3];
		}
		else if(string(argv[3]) == "EK")
		{
			algorithm = argv[3];
		}
		else if(string(argv[3]) == "FF")
		{
			algorithm = argv[3];
		}
		else
		{
			usage(argv);
		}
	}

	if(argc == 4)
	{
		usage(argv);
	}
	else if(string(argv[4]) == "-A" or string(argv[4]) == "--auto")
	{
		manual = false;
	}
	else if(string(argv[4]) == "-M" or string(argv[4]) == "--manual")
	{
		manual = true;
	}
	else
	{
		usage(argv);
	}

	executeMode(version, algorithm, manual);
}
