#include "Graph.h"

/* CONSTRUCTOR */

Graph::Graph() : lastEmplaced(minElements), edges(minElements), vertices(minElements)
{

}

Graph::Graph(uint maxFlights) : lastEmplaced(minElements), edges(minElements), vertices(minElements)
{
	edges[sourceWithDemand].emplace_back(Edge(sourceWithDemand, sinkWithDemand, maxFlights));

	vertices[sourceWithDemand].setDemand(-maxFlights);
	vertices[sinkWithDemand].setDemand(maxFlights);
}

Graph::Graph(const Graph &graph) : lastEmplaced(graph.lastEmplaced), edges(graph.edges), vertices(graph.vertices)
{

}

/* MODIFY METHODS */

void Graph::addEdge(const Vertex &origin, const Vertex &destination, int capacity, int lowerBound)
{
	if(capacity < 0) throw invalid_argument("capacity");
	if(lowerBound < 0) throw invalid_argument("lowerBound");

	uint originIndex = lastEmplaced;
	uint destinationIndex = originIndex + 1;

	vertices.emplace_back(origin);			// Afegeix el node de la ciutat d'origen
	vertices.emplace_back(destination);		// Afegeix el node de la ciutat de destí

	edges[sourceWithDemand].emplace_back(Edge(sourceWithDemand, originIndex, maxFlowValue, minFlowValue));			// Afegeix l'aresta del source al origen
	edges.emplace_back(vector<Edge>(1, Edge(originIndex, destinationIndex, uint(capacity), uint(lowerBound))));		// Afegeix l'aresta entre vols
	edges.emplace_back(vector<Edge>(1, Edge(destinationIndex, sinkWithDemand, maxFlowValue, minFlowValue)));		// Afegeix l'aresta del desti al sink

	lastEmplaced += 2;
}

void Graph::addNeighbour(uint index, const Edge &destination)
{
	edges[index].emplace_back(destination);
}

void Graph::updateMaxFlights(uint maxFlights)
{
	edges[sourceWithDemand][sinkWithDemand].setCapacity(maxFlights);

	vertices[sourceWithDemand].setDemand(-maxFlights);
	vertices[sinkWithDemand].setDemand(maxFlights);
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

vector<Edge>& Graph::getEdges(uint index)
{
	return this -> edges[index];
}

uint Graph::vertexSize() const
{
	return this -> vertices.size();
}