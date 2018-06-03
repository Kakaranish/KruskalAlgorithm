#include <iostream>
#include <cstdio>
#include <regex>

#include "Graph.h"
#include "Data structures/PriorityQueueMaxHeap.h"

#include <ctime>
void FindMinimumSpanningTree(std::string filename, bool graphIsDirected = true, bool isFirstVerticeIndexZero = true)
{
    //Loading graph from file
    Graph graph(graphIsDirected);
    graph.setIsFirstVerticeIndexZero(isFirstVerticeIndexZero);

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
    /*
                                        TODO:std::move here 
    */
    //Creating set of sorted egdes we can find in graph
    auto sortedEdges = graph.getSortedEdgesInPriorityQueue();

    LinkedList<Pair<unsigned, unsigned>> result;

    int biggestTreeSize = 1;
    while (!sortedEdges.isEmpty() && biggestTreeSize != numOfVertices)
    {
        //Getting edge data
        auto lowestEdge = sortedEdges.pop();
        unsigned fromVertice = lowestEdge.value.first,
                 toVertice = lowestEdge.value.second;
        int weight = lowestEdge.priority;

        int fromVerticeBelongsTo = indexOfTreeVerticeBelongsTo[fromVertice];
        int toVerticeBelongsTo = indexOfTreeVerticeBelongsTo[toVertice];

        //State at the beginning
        // std::cout << "(" << fromVertice << "," << toVertice << ")" << std::endl;
        // std::cout << "v[" << fromVertice << "] belongs to tree " << indexOfTreeVerticeBelongsTo[fromVertice] << std::endl;
        // std::cout << "v[" << toVertice << "] belongs to tree " << indexOfTreeVerticeBelongsTo[toVertice] << std::endl;
        // std::cout << "sizeOfTree[" << fromVerticeBelongsTo << "] = " << sizeOfTree[fromVerticeBelongsTo] << std::endl;
        // std::cout << "sizeOfTree[" << toVerticeBelongsTo << "] = " << sizeOfTree[toVerticeBelongsTo] << std::endl
        //           << std::endl;

        //Both vertices creating edge belongs to the same tree
        if (fromVerticeBelongsTo == toVerticeBelongsTo)
            continue;

        int indexOfBiggerTree = (sizeOfTree[fromVerticeBelongsTo] > sizeOfTree[toVerticeBelongsTo]) ? fromVerticeBelongsTo : toVerticeBelongsTo;
        int indexOfLowerTree = (indexOfBiggerTree == fromVerticeBelongsTo) ? toVerticeBelongsTo : fromVerticeBelongsTo;

        for (int i = 0; i < numOfVertices; i++)
        {
            //Transfer all vertices from lower tree to the bigger one
            if (indexOfTreeVerticeBelongsTo[i] == indexOfLowerTree)
                indexOfTreeVerticeBelongsTo[i] = indexOfBiggerTree;
        }

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