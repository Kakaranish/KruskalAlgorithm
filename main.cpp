#include <iostream>
#include <cstdio>
#include <regex>

#include "Graph.h"
void FindMinimumSpanningTree()
{
    //Load from file

    int *NumberOfTreeVerticeWithIndexBelongsTo = new int[10]; //size todo
}

int main(int argc, char *argv[])
{

    Graph graph(false);               //undirected graph
    graph.setFirstVerticeZero(false); //in file first vertice has index 1
    
    if (!graph.loadGraph("Res/z_zadania.txt"))
        std::cout << "Unable to load graph from given file." << std::endl;

    graph.showEdges();

    return 0;
}