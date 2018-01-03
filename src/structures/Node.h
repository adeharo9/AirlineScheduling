#ifndef AIRLINESCHEDULING_NODE_H
#define AIRLINESCHEDULING_NODE_H


class Node
{
public:
	/* ATTRIBUTES */

	int city;
	int time;
	int demand;

public:
	/* CONSTRUCTORS */

	Node() = default;
	Node(int city, int time, int demand = 0);

	/* DESTRUCTORS */

	~Node() = default;
};


#endif //AIRLINESCHEDULING_NODE_H
