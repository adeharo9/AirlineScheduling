#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int flow, int capacity, int lowerBound) : flow((uint) flow), capacity((uint) capacity), lowerBound((uint) lowerBound)
{
	if(flow < 0) throw invalid_argument("to");
	if(capacity < 0) throw invalid_argument("capacity");
	if(lowerBound < 0) throw invalid_argument("lowerBound");
}

/* SET METHODS */

void Edge::setLowerBound(int lowerBound)
{
	if(lowerBound < 0) throw invalid_argument("lowerBound");

	this -> lowerBound = (uint) lowerBound;
}

void Edge::setCapacity(int capacity)
{
	if(capacity < 0) throw invalid_argument("capacity");

	this -> capacity = (uint) capacity;
}

/* GET METHODS */

uint Edge::getN() const
{
	return this -> flow;
}

uint Edge::getLowerBound() const
{
	return this -> lowerBound;
}

uint Edge::getCapacity() const
{
	return this -> capacity;
}