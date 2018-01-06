#include "Benchmark.h"

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
	simulation.initialize();

	chrono.start(0);
	simulation.run();
	chrono.stop(0);

	simulation.end();
	simulation.reset();

	chrono.reset(0);
}