#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int to, int capacity, int lowerBound) : n(to), capacity(capacity), lowerBound(lowerBound)
{
	if(to < 0) throw invalid_argument("to");
	if(capacity < 0) throw invalid_argument("capacity");
	if(lowerBound < 0) throw invalid_argument("lowerBound");
}

/* SET METHODS */

void Edge::setLowerBound(int lowerBound)
{
	if(lowerBound < 0) throw invalid_argument("lowerBound");

	this -> lowerBound = lowerBound;
}

/* GET METHODS */

int Edge::getN() const
{
	return this -> n;
}

int Edge::getLowerBound() const
{
	return this -> lowerBound;
}

int Edge::getCapacity() const
{
	return this -> capacity;
}