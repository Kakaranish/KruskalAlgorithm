#include <iostream>
#include <cstdio>
#include <regex>

#include "Graph.h"
void FindMinimumSpanningTree(std::string filename, bool graphIsDirected = true, bool isFirstVerticeIndexZero = true)
{
    Graph graph(graphIsDirected);
    graph.setIsFirstVerticeIndexZero(isFirstVerticeIndexZero);

    if (!graph.loadGraph(filename))
    {
        std::cout << "Unable to load graph from given file." << std::endl;
        return;
    }
    const std::size_t &numOfVertices = graph.getNumOfVertices();

    //Every single vertice creates seperate tree

    unsigned *numOfTreeVerticeBelongsTo = new unsigned[numOfVertices],
             *sizeOfTree = new unsigned[numOfVertices];

    //Init of above arrays
    for (int i = 0; i < numOfVertices; i++)
    {
        numOfTreeVerticeBelongsTo[i] = i;
        sizeOfTree[i] = 1;
    }

    //Creating set of sorted egdes we can find in graph
}

int main(int argc, char *argv[])
{

    Graph graph(true);                      //undirected graph
    graph.setIsFirstVerticeIndexZero(false); //in file first vertice has index 1

    if (!graph.loadGraph("Res/z_zadania.txt"))
        std::cout << "Unable to load graph from given file." << std::endl;

    graph.showEdges();
    std::cout << graph.getNumOfVertices() << std::endl;



    return 0;
}