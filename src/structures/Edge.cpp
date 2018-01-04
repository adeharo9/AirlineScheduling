#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int to, int capacity, int lowerBound) : n((uint) to), capacity((uint) capacity), lowerBound((uint) lowerBound)
{
	if(to < 0) throw invalid_argument("to");
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
	return this -> n;
}

uint Edge::getLowerBound() const
{
	return this -> lowerBound;
}

uint Edge::getCapacity() const
{
	return this -> capacity;
}