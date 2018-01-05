#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int destination, int capacity, int lowerBound) : destination((uint) destination), capacity((uint) capacity), lowerBound((uint) lowerBound)
{
	if(destination < 0) throw invalid_argument("to");
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

uint Edge::getDestination() const
{
	return this -> destination;
}

uint Edge::getLowerBound() const
{
	return this -> lowerBound;
}

uint Edge::getCapacity() const
{
	return this -> capacity;
}