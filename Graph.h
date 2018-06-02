#ifndef _GRAPH_H
#define _GRAPH_H
#include <iostream>
#include <cstdio>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <regex>
#include <functional>

#include "Utility.h"
#include "LinkedList.h"

class Graph
{
  private:
	//Flags
	bool isDirected = true;
	bool firstVerticeIndexIsZero = true;
	std::size_t numOfVertices = 0;
	bool **adj_matrix = nullptr;

	void clearAdjMatrix();
	void dealocateAdjMatrix();

  public:
	//CONSTRUCTORS AND DESTRUCTOR
	Graph() = default;
	Graph(bool _isDirected);
	Graph(std::size_t _numOfVertices, bool _isDirected);
	~Graph();

	//UTILITY FUNCTIONS
	inline void setFirstVerticeIndexIsZero(bool value) { firstVerticeIndexIsZero = value; }
	inline const std::size_t &getNumOfVertices() { return numOfVertices; }

	bool loadGraph(std::string filename);
	void showAdjMatrix();
	void showEdges();
};

#endif