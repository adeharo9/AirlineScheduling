#ifndef AIRLINESCHEDULING_ARESTA_H
#define AIRLINESCHEDULING_ARESTA_H

#include <stdexcept>

typedef unsigned int uint;

using namespace std;

class Edge
{
private:
	/* ATTRIBUTES */

	uint flow;
	uint lowerBound;	// Lower bound
	uint capacity;	// Capacity

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


#endif //AIRLINESCHEDULING_ARESTA_H
