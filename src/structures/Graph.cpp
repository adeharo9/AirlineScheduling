#include "Graph.h"

/* CONSTRUCTOR */

Graph::Graph() : lastEmplaced(minElements), edges(minElements), vertices(minElements)
{

}

/* MODIFY METHODS */

void Graph::addEdge(const Vertex &origin, const Vertex &destination, int capacity, int lowerBound)
{
	if(capacity < 0) throw invalid_argument("capacity");
	if(lowerBound < 0) throw invalid_argument("lowerBound");

	uint originIndex = lastEmplaced;
	uint destinationIndex = originIndex + 1;

	vertices.emplace_back(origin);
	vertices.emplace_back(destination);

	edges[sourceWithDemand].emplace_back(Edge(sourceWithDemand, originIndex, minFlowValue, maxFlowValue));
	edges.emplace_back(vector<Edge>(1, Edge(originIndex, destinationIndex, uint(capacity), uint(lowerBound))));
	edges.emplace_back(vector<Edge>(1, Edge(destinationIndex, sinkWithDemand, minFlowValue, maxFlowValue)));

	lastEmplaced += 2;
}

void Graph::addNeighbour(uint index, const Edge &destination)
{
	edges[index].emplace_back(destination);
}

/* GET METHODS */

Vertex& Graph::getVertex(uint index)
{
	return this -> vertices[index];
}

Edge& Graph::getEdge(uint indexI, uint indexJ)
{
	return this -> edges[indexI][indexJ];
}

uint Graph::vertexSize() const
{
	return this -> vertices.size();
}