#include "Vertex.h"

/* CONSTRUCTORS */

Vertex::Vertex(int inCity, int inTime, int inDemand) : city((uint) inCity), time((uint) inTime), demand(inDemand)
{
	if(inCity < 0) throw invalid_argument("inCity");
	if(inTime < 0) throw invalid_argument("inTime");
}

/* SET METHODS */

void Vertex::setDemand(int inDemand)
{
	this -> demand = inDemand;
}

void Vertex::incrementDemand(int increment)
{
	if(increment < 0) throw invalid_argument("increment");

	this -> demand += increment;
}

void Vertex::decrementDemand(int decrement)
{
	if(decrement < 0) throw invalid_argument("decrement");

	this -> demand -= decrement;
}

/* GET METHODS */

uint Vertex::getCity() const
{
	return this -> city;
}

uint Vertex::getTime() const
{
	return this -> time;
}

int Vertex::getDemand() const
{
	return this -> demand;
}