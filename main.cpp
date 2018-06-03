#include <iostream>
#include <cstdio>
#include <regex>

#include "Graph.h"
#include "Data structures/PriorityQueueMaxHeap.h"

void FindMinimumSpanningTree(std::string filename, bool graphIsDirected = true, bool isFirstVerticeIndexZero = true)
{
    //Graph initialization
    Graph graph(graphIsDirected);
    graph.setIsFirstVerticeIndexZero(isFirstVerticeIndexZero);

    //Loading graph from file
    if (!graph.loadGraph(filename))
    {
        std::cout << "Unable to load graph from given file." << std::endl;
        return;
    }

    //Helper variables
    const std::size_t &numOfVertices = graph.getNumOfVertices();

    //Every single vertice creates seperate tree
    unsigned *indexOfTreeVerticeBelongsTo = new unsigned[numOfVertices],
             *sizeOfTree = new unsigned[numOfVertices];

    //Init of above arrays
    for (int i = 0; i < numOfVertices; i++)
    {
        indexOfTreeVerticeBelongsTo[i] = i;
        sizeOfTree[i] = 1;
    }

    //Creating set of sorted egdes we can find in graph
    auto sortedEdges = graph.getSortedEdgesInPriorityQueue();

    LinkedList<Pair<unsigned, unsigned>> result;

    //If this var is equal to numOfVertices that means we got spanning tree
    int biggestTreeSize = 1;
    while (!sortedEdges.isEmpty() && biggestTreeSize != numOfVertices)
    {
        //Getting edge data
        auto lowestEdge = sortedEdges.pop();
        unsigned fromVertice = lowestEdge.value.first,
                 toVertice = lowestEdge.value.second;
        int weight = lowestEdge.priority;

        //Getting indexes of trees our vertices belong to
        int fromVerticeBelongsTo = indexOfTreeVerticeBelongsTo[fromVertice];
        int toVerticeBelongsTo = indexOfTreeVerticeBelongsTo[toVertice];

        //Both vertices creating edge belongs to the same tree - we can ommit them
        if (fromVerticeBelongsTo == toVerticeBelongsTo)
            continue;

        //Helper variables
        int indexOfBiggerTree = (sizeOfTree[fromVerticeBelongsTo] > sizeOfTree[toVerticeBelongsTo]) ? fromVerticeBelongsTo : toVerticeBelongsTo;
        int indexOfLowerTree = (indexOfBiggerTree == fromVerticeBelongsTo) ? toVerticeBelongsTo : fromVerticeBelongsTo;

        //Transfer all vertices from lower tree to the bigger one
        for (int i = 0; i < numOfVertices; i++)
            if (indexOfTreeVerticeBelongsTo[i] == indexOfLowerTree)
                indexOfTreeVerticeBelongsTo[i] = indexOfBiggerTree;

        //After transfer we change size of both trees
        sizeOfTree[indexOfBiggerTree] += sizeOfTree[indexOfLowerTree];
        sizeOfTree[indexOfLowerTree] = 0;

        if (sizeOfTree[indexOfBiggerTree] > biggestTreeSize)
            biggestTreeSize = sizeOfTree[indexOfBiggerTree];

        result.push_back(Pair<unsigned, unsigned>(fromVertice, toVertice));
    }

    //Showing received spanning tree
    result.show(true);
}

int main(int argc, char *argv[])
{
    FindMinimumSpanningTree("Res/test.txt", false, true);

    return 0;
}