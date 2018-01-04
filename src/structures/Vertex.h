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

	Vertex(int city, int time, int demand = 0);

	/* DESTRUCTORS */

	~Vertex() = default;

	/* SET METHODS */

	void setDemand(int demand);

	void incrementDemand(int increment = 1);

	void decrementDemand(int decrement = 1);

	/* GET METHODS */

	uint getCity() const;

	uint getTime() const;

	int getDemand() const;
};


#endif // AIRLINESCHEDULING_VERTEX_H
