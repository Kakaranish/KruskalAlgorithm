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
	
	std::size_t numOfVertices = 0;
	std::size_t numOfEdges = 0;
	int **adj_matrix = nullptr;

	void clearAdjMatrix();
	void dealocateAdjMatrix();

  public:

	static const int infinity = std::numeric_limits<int>::max();

	//CONSTRUCTORS AND DESTRUCTOR
	Graph() = default;
	Graph(bool _isDirected);
	Graph(std::size_t _numOfVertices, bool _isDirected);
	~Graph();

	//UTILITY FUNCTIONS
	inline void setIsFirstVerticeIndexZero(bool value) { isFirstVerticeIndexZero = value; }
	inline const std::size_t &getNumOfVertices() { return numOfVertices; }

	bool loadGraph(std::string filename);
	void showAdjMatrix();
	void showEdges();

	PriorityQueueMaxHeap<Pair<unsigned, unsigned>, int> getSortedEdgesInPriorityQueue();

};

#endif