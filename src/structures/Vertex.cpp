#include "Vertex.h"

/* CONSTRUCTORS */

Vertex::Vertex(int city, int time, int demand) : city((uint) city), time((uint) time), demand(demand)
{
	if(city < 0) throw invalid_argument("city");
	if(time < 0) throw invalid_argument("time");
}

/* SET METHODS */

void Vertex::setDemand(int demand)
{
	this -> demand = demand;
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