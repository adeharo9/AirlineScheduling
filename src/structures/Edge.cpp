#include "Edge.h"

/* CONSTRUCTORS */

Edge::Edge(int to, int capacity, int lowerBound) : n(to), capacity(capacity), lowerBound(lowerBound)
{

}

/* SET METHODS */

void Edge::setLowerBound(int lowerBound)
{
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