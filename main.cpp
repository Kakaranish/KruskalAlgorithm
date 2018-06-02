#include <iostream>
#include <cstdio>
#include <regex>

#include "Graph.h"
void FindMinimumSpanningTree(std::string filename, bool graphIsDirected = true, bool firstVerticeIndexIsZero = true)
{
    Graph graph(graphIsDirected);
    graph.setFirstVerticeIndexIsZero(firstVerticeIndexIsZero);

    if(!graph.loadGraph(filename))
    {
        std::cout << "Unable to load graph from given file." << std::endl;
        return;
    }
    const std::size_t& numOfVertices = graph.getNumOfVertices();

    unsigned* numOfTreeVerticeBelongsTo = new unsigned[numOfVertices];
}

int main(int argc, char *argv[])
{

    Graph graph(false);               //undirected graph
    graph.setFirstVerticeIndexIsZero(false); //in file first vertice has index 1
    
    if (!graph.loadGraph("Res/z_zadania.txt"))
        std::cout << "Unable to load graph from given file." << std::endl;

    graph.showEdges();
    std::cout << graph.getNumOfVertices() << std::endl;

    return 0;
}