#ifndef AIRLINESCHEDULING_GRAPH_H
#define AIRLINESCHEDULING_GRAPH_H


#include <unordered_map>
#include <vector>

#include "Vertex.h"
#include "Edge.h"

using namespace std;

typedef unsigned int uint;

class Graph
{
public:

	/* ATTRIBUTES */

	static const uint sourceWithoutDemand = 0;
	static const uint sinkWithoutDemand = sourceWithoutDemand + 1;
	static const uint sourceWithDemand = sinkWithoutDemand + 1;
	static const uint sinkWithDemand = sourceWithDemand + 1;

	static const uint firstVertex = sinkWithDemand + 1;

private:

	static const uint minFlowValue = 0;
	static const uint maxFlowValue = 1;

	static const uint minElements =  sinkWithDemand + 1;

	uint lastEmplaced;

	vector<vector<Edge>> edges;
	vector<Vertex> vertices;

public:

	/* CONSTRUCTORS */

	Graph();

	/* MODIFY METHODS */

	void addEdge(const Vertex &origin, const Vertex &destination, int capacity = 0, int lowerBound = 0);

	void addNeighbour(uint index, const Edge &destination);

	/* GET METHODS */

	Vertex& getVertex(uint index);

	Edge& getEdge(uint indexI, uint indexJ);

	uint vertexSize() const;

};


#endif //AIRLINESCHEDULING_GRAPH_H
