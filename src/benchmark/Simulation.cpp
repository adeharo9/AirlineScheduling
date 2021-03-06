#include "Simulation.h"

const string Simulation::V1_NAME = "1";
const string Simulation::V2_NAME = "2";

const string Simulation::DATA_DIR = "./data/";
const string Simulation::INSTANCE_NAME = "instance";
const string Simulation::INSTANCE_SEPARATOR = "_";
const string Simulation::INSTANCE_EXTENSION = ".air";

const string Simulation::OUTPUT_DIR = "./results/output/";
const string Simulation::OUTPUT_MANUAL_DIR = "./";
const string Simulation::OUTPUT_FILENAME = "Output";
const string Simulation::OUTPUT_SEPARATOR = "_";
const string Simulation::OUTPUT_EXTENSION = ".txt";

const string Simulation::SIMULATIONS_DIR = "./results/simulations/";
const string Simulation::SIMULATIONS_FILENAME = "Resultado";
const string Simulation::SIMULATIONS_SEPARATOR = "_";
const string Simulation::SIMULATIONS_EXTENSION = ".txt";

Simulation::Simulation(Mode inMode)
{
	this -> setMode(inMode);
}

void Simulation::input()
{
	uint originCity;
	uint destinationCity;
	uint departureTime;
	uint arrivalTime;

	maxFlights = 0;

	while (inputFile >> originCity)	
	{
		inputFile >> destinationCity;
		inputFile >> departureTime;
		inputFile >> arrivalTime;

		Vertex origin(originCity, departureTime);
		Vertex destination(destinationCity, arrivalTime);

		graph.addEdge(origin, destination);

		++maxFlights;
	}

	inputFile.close();
}

void Simulation::manualInput()
{
	uint originCity;
	uint destinationCity;
	uint departureTime;
	uint arrivalTime;

	maxFlights = 0;

	while (cin >> originCity)
	{
		cin >> destinationCity;
		cin >> departureTime;
		cin >> arrivalTime;

		Vertex origin(originCity, departureTime);
		Vertex destination(destinationCity, arrivalTime);

		graph.addEdge(origin, destination);

		++maxFlights;
	}

	originalBasicGraph = graph;
}


void Simulation::load(uint index1, uint index2, uint index3)
{

	switch (mode)
	{
		case VERSION_ALL_ALL_MANUAL:
		case VERSION_1_ALL_MANUAL:
		case VERSION_2_ALL_MANUAL:
		case VERSION_1_DI_MANUAL:
		case VERSION_2_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			if(graph.vertexSize() > 0)
			{
				this -> manualInput();
			}
			break;

		default:
			instanceName = INSTANCE_NAME + INSTANCE_SEPARATOR + to_string(index1) + INSTANCE_SEPARATOR + to_string(index2) + INSTANCE_SEPARATOR + to_string(index3) + INSTANCE_EXTENSION;
			string filePath = DATA_DIR + instanceName;

			this -> inputFile.open(filePath, fstream::in);
			this -> input();
			break;
	}
}

void Simulation::setAlgorithm(Algorithm* inAlgorithm)
{
	this -> algorithm = inAlgorithm;
}

void Simulation::initialize()
{
	if(firstIteration)
	{
		firstIteration = false;

		if(needsInputGraph)
		{
			graph = originalBasicGraph;
		}

		switch (mode)
		{
			case VERSION_ALL_ALL_MANUAL:
			case VERSION_1_ALL_MANUAL:
			case VERSION_1_DI_MANUAL:
			case VERSION_1_EK_MANUAL:
			case VERSION_1_FF_DFS_MANUAL:
			case VERSION_1_DI_AUTO:
			case VERSION_1_EK_AUTO:
			case VERSION_1_FF_DFS_AUTO:
				version1();				
				break;

			case VERSION_2_ALL_MANUAL:
			case VERSION_2_DI_MANUAL:
			case VERSION_2_EK_MANUAL:
			case VERSION_2_FF_DFS_MANUAL:
			case VERSION_2_DI_AUTO:
			case VERSION_2_EK_AUTO:
			case VERSION_2_FF_DFS_AUTO:
				version2();				
				break;

			default:
				throw invalid_argument("mode");
		}

		originalCompleteGraph = graph;
	}
	else
	{
		graph = originalCompleteGraph;
	}

	deleteLowerBound();		// Eliminar els lower bound
	deleteDemand();			// Eliminar les demandes
    transformMax();
}


void Simulation::run()
{
	maxFlow = dicotomic(0, maxFlights, false);
}

int Simulation::dicotomic(uint low, uint high, bool lastIterationCalc)
{
	if (high == low)
	{
		if(lastIterationCalc)
		{
			originalBasicGraph.updateMaxFlights(low);
			originalCompleteGraph.updateMaxFlights(low);
			graph.updateMaxFlights(low);
			this -> initialize();
			algorithm -> algorithm(adjacenceMatrixGraph, adjacenceMatrixResidualGraph, 0, 1, graph.vertexSize());
		}

		return low;
	}
	else
	{
		uint k = (high + low) / 2;
		originalBasicGraph.updateMaxFlights(k);
		originalCompleteGraph.updateMaxFlights(k);
		graph.updateMaxFlights(k);
		this -> initialize();

		int neededFlow = k + maxFlights;

		adjacenceMatrixResidualGraph = imatrix(graph.vertexSize(), vector<int>(graph.vertexSize()));

		int flow = algorithm -> algorithm(adjacenceMatrixGraph, adjacenceMatrixResidualGraph, 0, 1, graph.vertexSize());

		if (flow < neededFlow)
		{
			return dicotomic(k + 1, high, true);
		}
		else
		{
			return dicotomic(low, k, false);
		}
	}
}

void Simulation::processResults()
{
	if(adjacenceMatrixGraph.empty())
	{
		cout << maxFlow << endl;
		outputFile << maxFlow << endl;
	}
	else
	{
		int k = adjacenceMatrixGraph[3][1]; //un lloc on es troba k
		int nvols = (adjacenceMatrixGraph.size() - 4) / 2;
		int flow = 0;

		if (adjacenceMatrixResidualGraph[3][1] == 0)
		{
			flow = k;
		}

		for (int i = 4; i < adjacenceMatrixGraph.size(); i += 2)
		{
			if (adjacenceMatrixResidualGraph[i][1] == 0)
			{
				++flow;
			}
		}

		if (flow == nvols + k)
		{
			printSol(adjacenceMatrixResidualGraph, adjacenceMatrixGraph);
		}
		else
		{
			cout << "No s'ha trobat cap solució." << endl;
			outputFile << "No s'ha trobat cap solució." << endl;
		}
	}
}

void Simulation::end()
{
	outputFile.open(outputFilePath, fstream::out | fstream::app);

	this -> processResults();

	outputFile.close();

	simulationsFile.open(simulationsFilePath, fstream::out | fstream::app);

	if(not simulationsFile.is_open())
	{
		simulationsFile.open(simulationsFilePath, fstream::out | fstream::trunc);
	}

	simulationsFile << instanceName << " " << maxFlow << endl;

	simulationsFile.close();

	firstIteration = true;
}

void Simulation::reset()
{
	graph = Graph();
	firstIteration = true;
}

void Simulation::setMode(Mode inMode)
{
	string versionName;
	string idOutput;
	string idSimulations;

	this -> mode = inMode;

	switch (inMode)
	{
		case VERSION_ALL_ALL_MANUAL:
		case VERSION_1_ALL_MANUAL:
		case VERSION_1_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_1_DI_AUTO:
		case VERSION_1_EK_AUTO:
		case VERSION_1_FF_DFS_AUTO:
			versionName = V1_NAME;
			break;

		case VERSION_2_ALL_MANUAL:
		case VERSION_2_DI_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
		case VERSION_2_DI_AUTO:
		case VERSION_2_EK_AUTO:
		case VERSION_2_FF_DFS_AUTO:
			versionName = V2_NAME;
			break;

		default:
			throw invalid_argument("mode");
	}

	switch (mode)
	{
		case VERSION_ALL_ALL_MANUAL:
		case VERSION_1_ALL_MANUAL:
		case VERSION_2_ALL_MANUAL:
		case VERSION_1_DI_MANUAL:
		case VERSION_2_DI_MANUAL:
		case VERSION_1_EK_MANUAL:
		case VERSION_2_EK_MANUAL:
		case VERSION_1_FF_DFS_MANUAL:
		case VERSION_2_FF_DFS_MANUAL:
			idOutput = "";
			idSimulations = "";
			needsInputGraph = true;
			break;

		case VERSION_1_DI_AUTO:
		case VERSION_2_DI_AUTO:
			idOutput = OUTPUT_SEPARATOR + DinicBlockingFlow::ID;
			idSimulations = SIMULATIONS_SEPARATOR + DinicBlockingFlow::ID;
			needsInputGraph = false;
			break;

		case VERSION_1_EK_AUTO:
		case VERSION_2_EK_AUTO:
			idOutput = OUTPUT_SEPARATOR + EdmondsKarp::ID;
			idSimulations = SIMULATIONS_SEPARATOR + EdmondsKarp::ID;
			needsInputGraph = false;
			break;

		case VERSION_1_FF_DFS_AUTO:
		case VERSION_2_FF_DFS_AUTO:
			idOutput = OUTPUT_SEPARATOR + FordFulkersonDFS::ID;
			idSimulations = SIMULATIONS_SEPARATOR + FordFulkersonDFS::ID;
			needsInputGraph = false;
			break;

		default:
			throw invalid_argument("mode");
	}

	outputFilePath = OUTPUT_DIR + OUTPUT_FILENAME + versionName + idOutput + OUTPUT_EXTENSION;
	simulationsFilePath = SIMULATIONS_DIR + SIMULATIONS_FILENAME + versionName + idSimulations + SIMULATIONS_EXTENSION;
}


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

void Simulation::deleteDemand()
{
	for (uint i = Graph::firstFlowNetworkVertex; i < graph.vertexSize(); ++i)
	{
		if (graph.getVertex(i).getDemand() > 0)	// Si demanda > 0 es un sink i va a t
		{
			graph.addNeighbour(i, Edge(i, 1, graph.getVertex(i).getDemand()));
			graph.getVertex(i).setDemand(0);
		}
		else if (graph.getVertex(i).getDemand() < 0)	// Si demanda < 0 es source i s va a ell
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

void Simulation::printSol(const vector<vector<int> >& residualGraph, const vector<vector<int> >& initialGraph)
{
	cout << maxFlow << endl;
	outputFile << maxFlow << endl;

	//si s'ha seguit una aresta amb capacitat 1, al graf final te capacitat 0
	int p = 1;

	for(int i = 4; i < residualGraph.size(); i += 2)	//origen
	{
		if (residualGraph[2][i] == 0)	//si el camí comença per el vertex i
		{
			int j = i;	

			while (residualGraph[j + 1][3] != 0)	// si NO es l'ultim vol que fa el pilot
			{
				cout << (j - 4) / 2 + 1 << " ";
				outputFile << (j - 4) / 2 + 1 << " ";

				bool found = false;

				for (int k = 4; k < residualGraph.size() and not found; k += 2)
				{
					if (residualGraph[j + 1][k] == 0 and initialGraph[j + 1][k] == 1)	//si el vol ha seguit per aquest camí
					{
						j = k;
						found = true;
					}
				}
			}
			cout << (j - 4) / 2 + 1 << endl;
			outputFile << (j - 4) / 2 + 1 << endl;

			++p;
		}
	}
	cout << endl;
}
