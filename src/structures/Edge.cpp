#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int inOrigin, int inDestination, int inCapacity, int inLowerBound) : origin(uint(inOrigin)), destination(uint(inDestination)), capacity(uint(inCapacity)), lowerBound(uint(inLowerBound))
{
	if(inOrigin < 0) throw invalid_argument("inOrigin");
	if(inDestination < 0) throw invalid_argument("inDestination");
	if(inCapacity < 0) throw invalid_argument("inCapacity");
	if(inLowerBound < 0) throw invalid_argument("inLowerBound");
}

/* SET METHODS */

void Edge::setLowerBound(int inLowerBound)
{
	if(inLowerBound < 0) throw invalid_argument("inLowerBound");

	this -> lowerBound = (uint) inLowerBound;
}

void Edge::setCapacity(int inCapacity)
{
	if(inCapacity < 0) throw invalid_argument("inCapacity");

	this -> capacity = (uint) inCapacity;
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