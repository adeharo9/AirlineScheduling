#include "Simulation.h"

const string Simulation::V1_NAME = "1";
const string Simulation::V2_NAME = "2";

const string Simulation::DATA_DIR = "./data/";
const string Simulation::INSTANCE_NAME = "instance";
const string Simulation::INSTANCE_SEPARATOR = "_";
const string Simulation::INSTANCE_EXTENSION = ".air";

const string Simulation::OUTPUT_DIR = "./results/output/";
const string Simulation::OUTPUT_FILENAME = "Output";
const string Simulation::OUTPUT_SEPARATOR = "_";
const string Simulation::OUTPUT_EXTENSION = ".txt";

const string Simulation::SIMULATIONS_DIR = "./results/simulations/";
const string Simulation::SIMULATIONS_FILENAME = "Resultado";
const string Simulation::SIMULATIONS_SEPARATOR = "_";
const string Simulation::SIMULATIONS_EXTENSION = ".txt";

Simulation::Simulation(Mode inMode) : mode(inMode)
{
	switch (inMode)
	{
		case VERSION_1_EK:
			outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + V1_NAME + OUTPUT_SEPARATOR + EdmondsKarp::ID + OUTPUT_EXTENSION;
			simulationssFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + V1_NAME + SIMULATIONS_SEPARATOR + EdmondsKarp::ID + SIMULATIONS_EXTENSION;
			break;

		case VERSION_1_FF_DFS:
			outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + V1_NAME + OUTPUT_SEPARATOR + FordFulkersonDFS::ID + OUTPUT_EXTENSION;
			simulationssFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + V1_NAME + SIMULATIONS_SEPARATOR + FordFulkersonDFS::ID + SIMULATIONS_EXTENSION;
			break;

		case VERSION_2_EK:
			outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + V2_NAME + OUTPUT_SEPARATOR + EdmondsKarp::ID + OUTPUT_EXTENSION;
			simulationssFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + V2_NAME + SIMULATIONS_SEPARATOR + EdmondsKarp::ID + SIMULATIONS_EXTENSION;
			break;

		case VERSION_2_FF_DFS:
			outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + V2_NAME + OUTPUT_SEPARATOR + FordFulkersonDFS::ID + OUTPUT_EXTENSION;
			simulationssFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + V2_NAME + SIMULATIONS_SEPARATOR + FordFulkersonDFS::ID + SIMULATIONS_EXTENSION;
			break;

		default:
			throw invalid_argument("mode");
	}
}

void Simulation::input()
{
	uint originCity;
	uint destinationCity;
	uint departureTime;
	uint arrivalTime;

	maxFlights = 0;

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

}


void Simulation::load(uint index1, uint index2, uint index3)
{
	instanceName = INSTANCE_NAME + INSTANCE_SEPARATOR + to_string(index1) + INSTANCE_SEPARATOR + to_string(index2) + INSTANCE_SEPARATOR + to_string(index3) + INSTANCE_EXTENSION;
	string filePath = DATA_DIR + instanceName;

	this -> instance.open(filePath, fstream::in);

	this -> input();
}

void Simulation::setAlgorithm(Algorithm* inAlgorithm)
{
	this -> algorithm = inAlgorithm;
}

void Simulation::initialize()
{
	switch (mode)
	{
		case VERSION_1_EK:
		case VERSION_1_FF_DFS:
			version1();				// Afegir arestes si es pot arribar d'un vol a un altre
			break;

		case VERSION_2_EK:
		case VERSION_2_FF_DFS:
			version2();				// Afegir arestes si es pot arribar d'un vol a un altre
			break;

		default:
			throw invalid_argument("mode");
	}

	deleteLowerBound();		// Eliminar els lower bound
	deleteDemand();			// Eliminar les demandes
    transformMax();
}


void Simulation::run()
{
	maxFlow = dicotomic(0, maxFlights);
}

int Simulation::dicotomic(uint low, uint high)
{
	if (high == low)
	{
		cout << "FOUND MIN: " << low << endl;	// Print solution here

		return low;

	}
	else
	{
		uint k = (high + low) / 2;
		graph.updateMaxFlights(k);
		this -> initialize();

		int neededFlow = k + maxFlights;
		int flow = algorithm -> algorithm(adjacenceMatrixGraph, 0, 1, graph.vertexSize());

		if (flow < neededFlow)
		{
			return dicotomic(k + 1, high);
		}
		else
		{
			return dicotomic(low, k);
		}
	}
}

void Simulation::end()
{
	results.open(simulationssFilePath, fstream::out | fstream::app);

	if(not results.is_open())
	{
		results.open(simulationssFilePath, fstream::out | fstream::trunc);
	}

	results << instanceName << " " << maxFlow << endl;

	results.close();
}

void Simulation::reset()
{
	graph = Graph();
}

/*
	afegeix arestes seguint el criteri sobre quines transicions son posibles de la versió 1
	per tot node destí comprobem per tot node origen si es possible fer transició
	cost n * n on n son els vols
*/
void Simulation::version1()
{
	for (uint destination = Graph::firstDestinationVertex; destination < graph.vertexSize(); destination += 2)	// destination es desti
	{
		for (uint origin = Graph::firstOriginVertex; origin < graph.vertexSize(); origin += 2)	// origin es origen
		{
			if (reachable(destination, origin))
			{
				graph.addNeighbour(destination, Edge(destination, origin, 1));	// aresta del desti destination al origen origin amb pes 1
			}
		}
	}
}

void Simulation::version2()
{
	for (uint destination = Graph::firstDestinationVertex; destination < graph.vertexSize(); destination += 2)	// destination es desti
	{
		queue<uint> visiting;
		vector<bool> visited(graph.vertexSize(), false);

		for (uint origin = Graph::firstOriginVertex; origin < graph.vertexSize(); origin += 2)	// origin es origen
		{
			if (reachable(destination, origin))	// per evitar fer calculs sobre el mateix vol
			{
				visited[origin] = true;
				uint nextDestination = graph.getEdge(origin, 0).getDestination();
				visiting.push(nextDestination);

				graph.addNeighbour(destination, Edge(destination, origin, 1));	// aresta del desti destination al origen origin amb pes 1
			}
		}

		while (not visiting.empty())
		{
			uint current = visiting.front();
			visiting.pop();

			for (uint origin = Graph::firstOriginVertex; origin < graph.vertexSize(); origin += 2)	// origin es origen
			{
				if (not visited[origin] and reachable(current, origin))
				{
					visited[origin] = true;

					uint nextDestination = graph.getEdge(origin, 0).getDestination();
					visiting.push(nextDestination);

					graph.addNeighbour(destination, Edge(destination, origin, 1));	// aresta del desti destination al origen origin amb pes 1
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

bool Simulation::reachable(uint destination, uint origin)
{
	return (origin + 1 != destination) and graph.getVertex(destination).getCity() == graph.getVertex(origin).getCity() and (int(graph.getVertex(origin).getTime()) - int(graph.getVertex(destination).getTime())) >= MIN_TRANSITION_TIME;
}