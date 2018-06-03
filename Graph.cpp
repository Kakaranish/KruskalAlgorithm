#ifndef _GRAPH_CPP
#define _GRAPH_CPP
#include "Graph.h"

/*
	PRIVATE METHODS
*/

void Graph::clearAdjMatrix()
{
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			adj_matrix[i][j] = std::numeric_limits<int>::max();
}
void Graph::dealocateAdjMatrix()
{
	for (int i = 0; i < numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;

	numOfVertices = 0;
	numOfEdges = 0;
	adj_matrix = nullptr;
}

/*
	PUBLIC METHODS
*/

//CONSTRUCTORS AND DESTRUCTOR
Graph::Graph(bool _isDirected = true) : isDirected(_isDirected) {}
Graph::Graph(std::size_t _numOfVertices, bool _isDirected = true) : isDirected(_isDirected),
																	numOfVertices(_numOfVertices)
{
	adj_matrix = new int *[numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
		adj_matrix[i] = new int[numOfVertices];

	clearAdjMatrix();
}
Graph::~Graph()
{
	if (!numOfVertices)
		return;

	for (int i = 0; i < numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;
}

//UTILITY FUNCTIONS
bool Graph::loadGraph(std::string filename)
{
	std::ifstream file;
	file.open(filename, std::ios::in | std::ios::binary);

	//Check if file with given filename exists
	if (!file.good())
		return false;

	std::string currLine;
	{
		std::size_t newNumOfVertices;

		//Trying to read first line containg information about amount of vertices
		std::getline(file, currLine);
		try
		{
			newNumOfVertices = std::stoi(currLine);
		}
		catch (std::invalid_argument &e)
		{
			return false;
			std::cout << e.what() << std::endl;
		}
		numOfVertices = newNumOfVertices;

		//If any adjacency matrix exists right now in memory and has different size that's required atm we have to deallocate it
		if (numOfVertices && !adj_matrix && numOfVertices != newNumOfVertices)
			dealocateAdjMatrix();
		else
		{
			adj_matrix = new int *[numOfVertices];
			for (int i = 0; i < numOfVertices; i++)
				adj_matrix[i] = new int[numOfVertices];

			clearAdjMatrix(); //Setting all fields in array to false
		}
	}

	LinkedList<int> edge;

	//On linux we have to remember about carriage return at the end of read line and add \r to the regex
	std::regex edgeRegex("\\([0-9]+,[0-9]+\\),\\-?[0-9]+\r?"); //? - one or no occurence
	std::string weightPrefix("),");
	//Adding next edges of the graph to adjacency matrix
	while (!file.eof())
	{
		std::getline(file, currLine);

		if (std::regex_match(currLine, edgeRegex))
		{
			edge = extractIntegers(currLine);

			int fromVertice = edge[0] - (isFirstVerticeIndexZero ? 0 : 1),
				toVertice = edge[1] - (isFirstVerticeIndexZero ? 0 : 1),
				&weight = edge[2];

			//Increasing num of edges
			if (fromVertice == toVertice)
				++numOfEdges;
			else
			{
				if (!isDirected)
					numOfEdges += 2;
				else
					++numOfEdges;
			}

			auto verticeIsIncorrect = [this](int &vertice) -> bool {
				return (vertice < 0 || vertice >= numOfVertices + !isFirstVerticeIndexZero);
			};

			if (verticeIsIncorrect(fromVertice) || verticeIsIncorrect(toVertice))
				throw std::out_of_range("Out of range in adjacency matrix");
			else
			{
				adj_matrix[fromVertice][toVertice] = weight;

				//If graph is undirected we add symmetric edge to adjacency matrix
				if (!isDirected)
					adj_matrix[toVertice][fromVertice] = weight;
			}
		}
	}

	return true;
}
void Graph::showAdjMatrix()
{
	for (int i = 0; i < numOfVertices; i++)
	{
		for (int j = 0; j < numOfVertices; j++)
			std::cout << adj_matrix[i][j] + (isFirstVerticeIndexZero ? 0 : 1) << "\t";
		std::cout << std::endl;
	}
}
void Graph::showEdges()
{
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			if (adj_matrix[i][j] != infinity)
				std::cout << "(" << i + (isFirstVerticeIndexZero ? 0 : 1) << "," << j + (isFirstVerticeIndexZero ? 0 : 1) << ")\t";
	std::cout << std::endl;
}

PriorityQueueMaxHeap<Pair<unsigned, unsigned>, int> Graph::getSortedEdgesInPriorityQueue()
{
	PriorityQueueMaxHeap<Pair<unsigned, unsigned>, int> edges(numOfEdges, false);
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			if (adj_matrix[i][j] != Graph::infinity)
				if (!isDirected && j <= i)
					edges.push(Pair<unsigned, unsigned>(i, j), adj_matrix[i][j]);
	return edges;
}

#endif
