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
			adj_matrix[i][j] = false;
}
void Graph::dealocateAdjMatrix()
{
	for (int i = 0; i < numOfVertices; i++)
		delete[] adj_matrix[i];
	delete[] adj_matrix;

	numOfVertices = 0;
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
	adj_matrix = new bool *[numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
		adj_matrix[i] = new bool[numOfVertices];

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

	//Sprawdzamy, czy zadany plik istnieje
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
			adj_matrix = new bool *[numOfVertices];
			for (int i = 0; i < numOfVertices; i++)
				adj_matrix[i] = new bool[numOfVertices];

			clearAdjMatrix(); //Setting all fields in array to false
		}
	}

	LinkedList<int> edge;

	//On linux we have to remember about carriage return at the end of read line and add \r to the regex
	std::regex pairRegex("\\([0-9]+,[0-9]+\\)\r?");

	//Adding next edges of the graph to adjacency matrix
	while (!file.eof())
	{
		std::getline(file, currLine);

		if (std::regex_match(currLine, pairRegex))
		{
			edge = extractIntegers(currLine);
			if (edge[0] < 0 || edge[0] >= numOfVertices + !firstVertIsZero || edge[1] < 0 || edge[1] >= numOfVertices + !firstVertIsZero)
				throw std::out_of_range("Out of range in adjacency matrix");
			else
			{
				adj_matrix[firstVertIsZero ? edge[0] : edge[0] - 1][firstVertIsZero ? edge[1] : edge[1] - 1] = true;

				//If graph is undirected
				if (!isDirected)
					adj_matrix[firstVertIsZero ? edge[1] : edge[1] - 1][firstVertIsZero ? edge[0] : edge[0] - 1] = true;
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
			std::cout << adj_matrix[i][j] << "\t";
		std::cout << std::endl;
	}
}
void Graph::showEdges()
{
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			if (adj_matrix[i][j])
				std::cout << "(" << i << "," << j << ")\t";
	std::cout << std::endl;
}

#endif
