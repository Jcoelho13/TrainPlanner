// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <list>
#include "MutablePriorityQueue.h"
#include "VertexEdge.h"

using namespace std;

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w, int price);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w, int price);

    int getNumVertex() const;
    bool removeEdge(const int &source, const int &dest);
    std::vector<Vertex *> getVertexSet() const;

    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

    /** Implementation of the Edmonds-Karp algorithm
     * @brief Complexity O(|V|*|E|^2)
     * @param source id of the source vertex
     * @param target id of the target vertex
     */
    void edmondsKarp(int source, int target);

    /** Function that goes through the graph and returns the pairs of stations with the most trains
     * @return list of pairs of stations with the most trains
     * @brief Complexity O(|V|^2+|E|^2)
     */
    list<pair<int, int>> mostTrains();

    /** Implementation of the Dijkstra algorithm
     * @brief Complexity O(n^2) where n is the number of connections
     */
    void dijkstra(int source);

protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */