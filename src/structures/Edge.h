#ifndef AIRLINESCHEDULING_ARESTA_H
#define AIRLINESCHEDULING_ARESTA_H

#include <stdexcept>

using namespace std;

class Edge
{
private:
	/* ATTRIBUTES */

	int n;
	int lowerBound;	// Lower bound
	int capacity;	// Capacity

public:
	/* CONSTRUCTORS */

	Edge() = default;

	Edge(int to, int capacity, int lowerBound = 0);

	/* DESTRUCTORS */

	~Edge() = default;

	/* SET METHODS */

	void setLowerBound(int lowerBound);

	/* GET METHODS */

	int getN() const;

	int getLowerBound() const;

	int getCapacity() const;
};


#endif //AIRLINESCHEDULING_ARESTA_H
