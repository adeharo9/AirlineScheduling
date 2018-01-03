#ifndef AIRLINESCHEDULING_ARESTA_H
#define AIRLINESCHEDULING_ARESTA_H


class Aresta
{
public:
	/* ATTRIBUTES */

	int n;
	int lw;		//lower bound
	int cap;	//capacity

	/* CONSTRUCTORS*/

	Aresta();
	Aresta(int to, int c);
};


#endif //AIRLINESCHEDULING_ARESTA_H
