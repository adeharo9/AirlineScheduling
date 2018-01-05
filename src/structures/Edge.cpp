#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int origin, int destination, int capacity, int lowerBound) : origin(uint(origin)), destination(uint(destination)), capacity(uint(capacity)), lowerBound(uint(lowerBound))
{
	if(origin < 0) throw invalid_argument("origin");
	if(destination < 0) throw invalid_argument("destination");
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

uint Edge::getOrigin() const
{
	return this -> origin;
}

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