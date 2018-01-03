#ifndef AIRLINESCHEDULING_NODE_H
#define AIRLINESCHEDULING_NODE_H


class Vertex
{
public:
	/* ATTRIBUTES */

	int city;
	int time;
	int demand;

public:
	/* CONSTRUCTORS */

	Vertex() = default;
	Vertex(int city, int time, int demand = 0);

	/* DESTRUCTORS */

	~Vertex() = default;
};


#endif //AIRLINESCHEDULING_NODE_H
