#ifndef AIRLINESCHEDULING_EDGE_H
#define AIRLINESCHEDULING_EDGE_H


#include <stdexcept>

typedef unsigned int uint;

using namespace std;

class Edge
{
private:

	/* ATTRIBUTES */

	uint flow;
	uint lowerBound;
	uint capacity;

public:

	/* CONSTRUCTORS */

	Edge() = default;

	Edge(int flow, int capacity, int lowerBound = 0);

	/* DESTRUCTORS */

	~Edge() = default;

	/* SET METHODS */

	void setLowerBound(int lowerBound);

	void setCapacity(int capacity);

	/* GET METHODS */

	uint getN() const;

	uint getLowerBound() const;

	uint getCapacity() const;
};


#endif // AIRLINESCHEDULING_EDGE_H
