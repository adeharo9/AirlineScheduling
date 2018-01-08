#include "benchmark/Benchmark.h"

int main ()
{
	Benchmark benchmark;
	//EdmondsKarp edmondsKarp;

	benchmark.initialize();
	benchmark.run();
	//benchmark.runSingle(100, 10, 10, &edmondsKarp);
}
