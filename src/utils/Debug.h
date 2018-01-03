//
// Created by adeha on 03/01/2018.
//

#ifndef AIRLINESCHEDULING_DEBUG_H
#define AIRLINESCHEDULING_DEBUG_H

#include <iostream>
#include <vector>

#include "../structures/Aresta.h"
#include "../structures/Node.h"

using namespace std;

class Debug
{
public:
	static void printState(const vector<Node>& n, const vector<vector<Aresta>>& g);
};


#endif //AIRLINESCHEDULING_DEBUG_H
