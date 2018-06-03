#ifndef _GRAPH_H
#define _GRAPH_H
#include <iostream>
#include <cstdio>
#include <fstream>
#include <exception>
#include <regex>
#include <functional>
#include <limits>

#include "Utility.h"
#include "Data structures/LinkedList.h"
#include "Data structures/Pair.h"
#include "Data structures/PriorityQueueMaxHeap.h"

class Graph
{
  private:
	//Flags
	bool isDirected = true;
	bool isFirstVerticeIndexZero = true;

	//Fields
	std::size_t numOfVertices = 0;
	std::size_t numOfEdges = 0;
	int **adj_matrix = nullptr;

	//Methods
	void clearAdjMatrix();
	void dealocateAdjMatrix();

  public:
	static const int infinity = std::numeric_limits<int>::max();

	//Inline methods
	inline void setIsFirstVerticeIndexZero(bool value) { isFirstVerticeIndexZero = value; }
	inline const std::size_t &getNumOfVertices() { return numOfVertices; }

	//Constructor & destructor section
	Graph() = default;
	Graph(bool _isDirected);
	Graph(std::size_t _numOfVertices, bool _isDirected);
	~Graph();

	//Utility methods
	bool loadGraph(std::string filename);
	void showAdjMatrix();
	void showEdges();

	PriorityQueueMaxHeap<Pair<unsigned, unsigned>, int> getSortedEdgesInPriorityQueue();
};

#endif