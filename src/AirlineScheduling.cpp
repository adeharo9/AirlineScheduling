#include "benchmark/Benchmark.h"

int main ()
{
	Benchmark benchmark;
	EdmondsKarp edmondsKarp;

	//benchmark.run();
	benchmark.runSingle(100, 10, 1, &edmondsKarp);
}
