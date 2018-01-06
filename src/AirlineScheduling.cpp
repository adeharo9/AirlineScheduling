#include <iostream>

#include "algorithms/EdmondsKarp.h"
#include "benchmark/Simulation.h"

int main ()
{
	Simulation simulation;
	EdmondsKarp edmondsKarp;
	simulation.load(100, 10, 1);
	simulation.setAlgorithm(&edmondsKarp);
	simulation.initialize();
	simulation.run();
	simulation.end();
}
