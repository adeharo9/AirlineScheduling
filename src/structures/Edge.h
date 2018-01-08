#ifndef AIRLINESCHEDULING_EDGE_H
#define AIRLINESCHEDULING_EDGE_H


#include <stdexcept>

typedef unsigned int uint;

using namespace std;

class Edge
{
private:

	/* ATTRIBUTES */

	uint origin;
	uint destination;

	uint capacity;
	uint lowerBound;

public:

	/* CONSTRUCTORS */

	Edge() = default;

	Edge(int inOrigin, int inDestination, int inCapacity, int inLowerBound = 0);

	/* DESTRUCTORS */

	~Edge() = default;

	/* SET METHODS */

	void setLowerBound(int inLowerBound);

	void setCapacity(int inCapacity);

	/* GET METHODS */

	uint getOrigin() const;

	uint getDestination() const;

	uint getLowerBound() const;

	uint getCapacity() const;
};


#endif // AIRLINESCHEDULING_EDGE_H
