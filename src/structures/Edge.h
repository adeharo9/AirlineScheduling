#ifndef AIRLINESCHEDULING_ARESTA_H
#define AIRLINESCHEDULING_ARESTA_H


class Edge
{
public:
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
};


#endif //AIRLINESCHEDULING_ARESTA_H
