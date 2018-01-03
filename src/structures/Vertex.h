#ifndef AIRLINESCHEDULING_NODE_H
#define AIRLINESCHEDULING_NODE_H


class Vertex
{
private:
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

	/* GET METHODS */

	int getCity() const;

	int getTime() const;

	int getDemand() const;
};


#endif //AIRLINESCHEDULING_NODE_H
