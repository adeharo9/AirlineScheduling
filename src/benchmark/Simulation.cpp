#include "Simulation.h"

const string Simulation::DATA_DIR = "./data/";
const string Simulation::INSTANCE_NAME = "instance";
const string Simulation::INSTANCE_SEPARATOR = "_";
const string Simulation::INSTANCE_EXTENSION = ".air";

const string Simulation::RESULTS_DIR = "./results/";
const string Simulation::RESULTS_V1_FILENAME = "Resultado1";
const string Simulation::RESULTS_V2_FILENAME = "Resultado2";
const string Simulation::RESULTS_EXTENSION = ".txt";

const string Simulation::RESULTS_V1_FILEPATH = RESULTS_DIR + RESULTS_V1_FILENAME + RESULTS_EXTENSION;
const string Simulation::RESULTS_V2_FILEPATH = RESULTS_DIR + RESULTS_V2_FILENAME + RESULTS_EXTENSION;

void Simulation::input()
{
	uint originCity;
	uint destinationCity;
	uint departureTime;
	uint arrivalTime;

	uint maxFlights = 0;

	while (instance >> originCity)	// operacions descrites a la pagina 390 del llibre
	{
		instance >> destinationCity;
		instance >> departureTime;
		instance >> arrivalTime;

		Vertex origin(originCity, departureTime);
		Vertex destination(destinationCity, arrivalTime);

		graph.addEdge(origin, destination);

		++maxFlights;
	}

	instance.close();

	graph.updateMaxFlights(maxFlights);
}

void Simulation::load(uint index1, uint index2, uint index3)
{
	instanceName = INSTANCE_NAME + INSTANCE_SEPARATOR + to_string(index1) + INSTANCE_SEPARATOR + to_string(index2) + INSTANCE_SEPARATOR + to_string(index3) + INSTANCE_EXTENSION;
	string filePath = DATA_DIR + instanceName;

	this -> instance.open(filePath, fstream::in);

	this -> input();
}

void Simulation::setAlgorithm(Algorithm* algorithm)
{
	this -> algorithm = algorithm;
}

void Simulation::initialize()
{
	version1();				// Afegir arestes si es pot arribar d'un vol a un altre
	deleteLowerBound();		// Eliminar els lower bound
	deleteDemand();			// Eliminar les demandes
	transformMax();
}

void Simulation::run()
{
	maxFlow = algorithm -> algorithm(adjacenceMatrixGraph, 0, 1, graph.vertexSize());
}

void Simulation::end()
{
	results.open(RESULTS_V1_FILENAME, fstream::out | fstream::app);

	if(not results.is_open())
	{
		results.open(RESULTS_V1_FILENAME, fstream::out | fstream::trunc);
	}

	results << instanceName << " " << maxFlow << endl;
}


/*
	afegeix arestes segibs el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void Simulation::version1()
{
	for (uint i = Graph::firstDestinationVertex; i < graph.vertexSize(); i += 2)	// i es desti
	{
		for (uint j = Graph::firstOriginVertex; j < graph.vertexSize(); j += 2)	// j es origen
		{
			if (j != i - 1)	// per evitar fer calculs sobre el mateix vol
			{
				if (graph.getVertex(i).getCity() == graph.getVertex(j).getCity() and int(graph.getVertex(j).getTime()) - int(graph.getVertex(i).getTime()) >= MIN_TRANSITION_TIME)
				{
					// aresta del desti i al origen j amb pes 1
					graph.addNeighbour(i, Edge(i, j, 1));
				}
			}
		}
	}
}
/*
  elimina els lower bound de les arestes i actualitza les demandes
  les uniques arestes amb lower suerten de les ciutats d'origen
*/
void Simulation::deleteLowerBound()
{
	for (uint i = Graph::firstOriginVertex; i < graph.vertexSize(); i += Graph::originStepSize)
	{
		//la primera aresta es la del viatge
		graph.getEdge(i, 0).setCapacity(graph.getEdge(i, 0).getCapacity() - graph.getEdge(i, 0).getLowerBound());
		graph.getEdge(i, 0).setLowerBound(0);

		//sumo 1 a la demanda de l'origen, i resto 1 a la de destí
		graph.getVertex(i).incrementDemand();
		graph.getVertex(i + 1).decrementDemand();
	}
}

/*
  elimina les demandes  i actualizta el sink i drain reals amb les
  arestes necessaries
*/
void Simulation::deleteDemand()
{
	for (uint i = Graph::firstFlowNetworkVertex; i < graph.vertexSize(); ++i)
	{
		if (graph.getVertex(i).getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			graph.addNeighbour(i, Edge(i, 1, graph.getVertex(i).getDemand()));
			graph.getVertex(i).setDemand(0);
		}
		else if (graph.getVertex(i).getDemand() < 0)	// Si es source s va a el
		{
			graph.addNeighbour(Graph::sourceWithoutDemand, Edge(Graph::sourceWithoutDemand, i, -graph.getVertex(i).getDemand()));
			graph.getVertex(i).setDemand(0);
		}
	}
}

void Simulation::transformMax()
{
	adjacenceMatrixGraph = imatrix(graph.vertexSize(), vector<int>(graph.vertexSize(), 0));

	for(uint i = Graph::firstElement; i < graph.vertexSize(); ++i)
	{
		for (uint j = 0; j < graph.getEdges(i).size(); ++j)
		{
			adjacenceMatrixGraph[i][graph.getEdge(i, j).getDestination()] = graph.getEdge(i, j).getCapacity();
		}
	}
}