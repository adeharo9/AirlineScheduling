#ifndef AIRLINESCHEDULING_ARESTA_H
#define AIRLINESCHEDULING_ARESTA_H


class Aresta
{
public:
	/* ATTRIBUTES */

	int n;
	int lowerBound;	//lower bound
	int capacity;	//capacity

public:
	/* CONSTRUCTORS*/

	Aresta() = default;
	Aresta(int to, int capacity, int lowerBound = 0);

	/* DESTRUCTORS */

	~Aresta() = default;
};


#endif //AIRLINESCHEDULING_ARESTA_H
