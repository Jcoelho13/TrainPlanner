// By: Gonçalo Leão

#include <map>
#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w, int price) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w, price);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w, int price) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, price);
    auto e2 = v2->addEdge(v1, w, price);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

void Graph::edmondsKarp(int source, int target) {
    Vertex* s = findVertex(source);
    Vertex* t = findVertex(target);
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");

    // Reset the flows
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    // Loop to find augmentation paths
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

void Graph::dijkstra(int source) {
    MutablePriorityQueue<Vertex> q;

    for(auto v : vertexSet) {
        v->setDist(INF);
        v->setCost(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    findVertex(source)->setDist(0);
    findVertex(source)->setCost(0);
    q.insert(findVertex(source));


    while(!q.empty()) {
        auto u = q.extractMin();
        u->setVisited(true);

        for(auto &e : u->getAdj()) {
            Vertex* v = e->getDest();
            if (!v->isVisited() && u->getCost() != INF && v->getCost() > u->getCost() + e->getWeight() * e->getPrice()) {
                v->setDist(u->getDist() + e->getWeight());
                v->setCost(u->getCost() + e->getWeight() * e->getPrice());
                v->setPath(e);
                q.insert(v);
            }
        }
    }
}

bool Graph::removeEdge(const int &source, const int &dest) {
    Vertex * srcVertex = findVertex(source);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

list<pair<int, int>> Graph::mostTrains() {

    double maxflow = -10;
    list<pair<int, int>> maxflowstations;

    map<int, double> weightSumMap;  // map< station id, weight of the edges >
    for (auto v : vertexSet) {
        double weightSum = 0;
        for (Edge* edge : v->getAdj()) {
            weightSum += 2*(edge->getWeight());
        }
        weightSumMap[v->getId()] = weightSum;
    }

    // sort the map in descending order of their weightSum
    vector<pair<int, double>> sortedStations(weightSumMap.begin(), weightSumMap.end());
    sort(sortedStations.begin(), sortedStations.end(),[](const pair<int, double>& a,const pair<int, double>& b) {return a.second > b.second;});

    for (auto it1 = sortedStations.begin(); it1 != sortedStations.end(); ++it1) {
        int station1_id = it1->first;
        if (it1->second < maxflow) {
            break;
        }

        double flow = 0;
        for (auto it2 = it1; it2 != sortedStations.end(); ++it2) {
            int station2_id = it2->first;
            if (it2->second < maxflow) {
                break;
            }
            if (station1_id == station2_id) {
                continue;
            }
            else {
                edmondsKarp(station1_id, station2_id);

                for (const auto e : findVertex(station1_id)->getAdj()) {
                    flow += e->getFlow();
                }

                if(flow > maxflow) {
                    maxflow = flow;
                    maxflowstations.clear(); //apagar tudo da lista dupla de estações

                    maxflowstations.push_back({station1_id, station2_id}); //adicionar par de estações à lista de estações com maxflow maior;
                }

                else if(flow==maxflow) {
                    maxflowstations.push_back({station1_id, station2_id}); //adicionar par à lista de estações com maxflow maior;
                }
            }
        }
    }

    return maxflowstations;
}