#ifndef AIRLINESCHEDULING_NODE_H
#define AIRLINESCHEDULING_NODE_H


class Node
{
public:
	/* ATTRIBUTES */

	int city;
	int time;
	int demanda;

public:
	/* CONSTRUCTORS*/

	Node() = default;
	Node(int city, int time, int demanda = 0);

	/* DESTRUCTORS */

	~Node() = default;
};


#endif //AIRLINESCHEDULING_NODE_H
