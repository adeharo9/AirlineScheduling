#ifndef AIRLINESCHEDULING_VERTEX_H
#define AIRLINESCHEDULING_VERTEX_H


#include <stdexcept>

typedef unsigned int uint;

using namespace std;

class Vertex
{
private:

	/* ATTRIBUTES */

	uint city;
	uint time;
	int demand;

public:

	/* CONSTRUCTORS */

	Vertex() = default;

	Vertex(int inCity, int inTime, int inDemand = 0);

	Vertex(const Vertex &vertex);

	/* DESTRUCTORS */

	~Vertex() = default;

	/* SET METHODS */

	void setDemand(int inDemand);

	void incrementDemand(int increment = 1);

	void decrementDemand(int decrement = 1);

	/* GET METHODS */

	uint getCity() const;

	uint getTime() const;

	int getDemand() const;
};


#endif // AIRLINESCHEDULING_VERTEX_H
