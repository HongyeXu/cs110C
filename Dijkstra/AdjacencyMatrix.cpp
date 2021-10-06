#include "AdjacencyMatrix.h"
#include <iostream>
#include "List.h"
using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
    //Row 0
    adjMat[0][0] = 0;
    adjMat[0][1] = 120;
    adjMat[0][2] = 150;
    adjMat[0][3] = infinity;
    adjMat[0][4] = infinity;
    adjMat[0][5] = 500;

    //Row 1
    adjMat[1][0] = 120;
    adjMat[1][1] = 0;
    adjMat[1][2] = infinity;
    adjMat[1][3] = 75;
    adjMat[1][4] = infinity;
    adjMat[1][5] = 350;

    //Row 2
    adjMat[2][0] = 150;
    adjMat[2][1] = infinity;
    adjMat[2][2] = 0;
    adjMat[2][3] = infinity;
    adjMat[2][4] = 250;
    adjMat[2][5] = infinity;

    //Row 3
    adjMat[3][0] = infinity;
    adjMat[3][1] = 75;
    adjMat[3][2] = infinity;
    adjMat[3][3] = 0;
    adjMat[3][4] = 150;
    adjMat[3][5] = infinity;

    //Row 4
    adjMat[4][0] = infinity;
    adjMat[4][1] = infinity;
    adjMat[4][2] = 250;
    adjMat[4][3] = 150;
    adjMat[4][4] = 0;
    adjMat[4][5] = infinity;

    //Row 5
    adjMat[5][0] = 500;
    adjMat[5][1] = 350;
    adjMat[5][2] = infinity;
    adjMat[5][3] = infinity;
    adjMat[5][4] = infinity;
    adjMat[5][5] = 0;

    cities[0] = "SFO";
    cities[1] = "LAX";
    cities[2] = "LAS";
    cities[3] = "PHX";
    cities[4] = "DEN";
    cities[5] = "JFK";
}


void AdjacencyMatrix::Dijkstra()
{
    List vertexSet;
    //main purpose: gives postion 1 the vertex 0
    //but also gives other positions vertex 0, will change later
    for (int pos = 1; pos <= numOfVertices; pos++)
        vertexSet.insert(pos, 0);   

    //Initialize the weights
    for (int v = 0; v < numOfVertices; v++)
        weight[v] = adjMat[0][v];


    for (int i = 1; i < numOfVertices; i++)
    {
        int min = 99999;
        //Find smallest weight[v] such that v is not in vertexSet
        int vertexWithSmallest;
        for (int v = 0; v < numOfVertices; v++)
        {
            if (!(vertexSet.linearSearch(v)))
            {
                if (weight[v] < min)
                {
                    min = weight[v];
                    vertexWithSmallest = v;
                }
            }
            //add such v to vertexSet
            vertexSet.setEntry(i + 1, vertexWithSmallest);


            // Check weight[u] for all u not in vertexSet
            for (int u = 0; u < numOfVertices; u++)
            {
                if (!(vertexSet.linearSearch(u)))
                {
                    if (weight[u] > weight[v] + adjMat[v][u])
                        weight[u] = weight[v] + adjMat[v][u];
                }
            }
        }
    }

    //finally print out the result
    for (int i = 0; i < numOfVertices; i++)
    {
        cout << "Cost from SFO to " << cities[i] << " is $" << weight[i] << endl;
    }
}