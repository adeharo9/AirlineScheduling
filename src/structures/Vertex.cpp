#include "Vertex.h"

/* CONSTRUCTORS */

Vertex::Vertex(int city, int time, int demand) : city(city), time(time), demand(demand)
{

}

/* GET METHODS */

int Vertex::getCity() const
{
	return this -> city;
}

int Vertex::getTime() const
{
	return this -> time;
}

int Vertex::getDemand() const
{
	return this -> demand;
}