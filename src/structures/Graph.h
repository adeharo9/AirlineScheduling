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

	static const uint firstElement = 0;
	static const uint sourceWithoutDemand = firstElement;
	static const uint sinkWithoutDemand = sourceWithoutDemand + 1;
	static const uint sourceWithDemand = sinkWithoutDemand + 1;
	static const uint sinkWithDemand = sourceWithDemand + 1;

	static const uint firstVertex = sinkWithDemand + 1;

	static const uint firstFlowNetworkVertex = sourceWithDemand;

	static const uint firstOriginVertex = sinkWithDemand + 1;
	static const uint firstDestinationVertex = firstOriginVertex + 1;

	static const uint originStepSize = sourceWithDemand - sourceWithoutDemand;
	static const uint destinationStepSize = sinkWithDemand - sinkWithoutDemand;

private:

	static const uint minFlowValue = 0;
	static const uint maxFlowValue = 1;

	static const uint minElements =  sinkWithDemand + 1;

	static const uint sinkWithDemandListIndex = 0;

	uint lastEmplaced;

	vector<vector<Edge>> edges;
	vector<Vertex> vertices;

public:

	/* CONSTRUCTORS */

	Graph();

	explicit Graph(uint maxFlights);

	Graph(const Graph &graph);

	/* MODIFY METHODS */

	void addEdge(const Vertex &origin, const Vertex &destination);

	void addNeighbour(uint index, const Edge &destination);

	void updateMaxFlights(uint maxFlights);

	/* GET METHODS */

	Vertex& getVertex(uint index);

	Edge& getEdge(uint indexI, uint indexJ);

	vector<Edge>& getEdges(uint index);

	uint vertexSize() const;

};


#endif //AIRLINESCHEDULING_GRAPH_H
