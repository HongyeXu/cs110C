#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H
#include <iostream>
#include <string>
using namespace std;

class AdjacencyMatrix
{
private:
    const int infinity = 99999;
    static const int numOfVertices = 6;
    int adjMat[numOfVertices][numOfVertices];
    int weight[numOfVertices];
    string cities[numOfVertices];
public:
    AdjacencyMatrix();
    int getWeight(int row, int column)
    {
        return adjMat[row][column];
    }
    void Dijkstra();
};

#endif