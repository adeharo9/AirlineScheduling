#ifndef AIRLINESCHEDULING_NODE_H
#define AIRLINESCHEDULING_NODE_H


class Node
{
public:
	/* ATTRIBUTES */

	int ciutat;
	int hora;
	int demanda;

	/* CONSTRUCTORS*/

	Node();
	Node(int c, int h);
};


#endif //AIRLINESCHEDULING_NODE_H
