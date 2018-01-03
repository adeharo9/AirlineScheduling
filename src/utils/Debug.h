#ifndef AIRLINESCHEDULING_DEBUG_H
#define AIRLINESCHEDULING_DEBUG_H

#include <iostream>
#include <vector>

#include "../structures/Edge.h"
#include "../structures/Vertex.h"

using namespace std;

class Debug
{
public:
	static void printState(const vector<Vertex>& n, const vector<vector<Edge>>& g);
};


#endif //AIRLINESCHEDULING_DEBUG_H
