#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

struct Edge {
    int to;
    int weight;
};

class Graph {
public:
    virtual void addEdge(int u, int v, int weight) = 0;
    virtual bool hasEdge(int u, int v) = 0;
    virtual std::vector<Edge> getNeighbors(int u) = 0;
    virtual int getV() = 0;
    virtual ~Graph() {}
};

class AdjList : public Graph {
private:
    int V;
    std::vector<std::list<Edge>> list;
public:
    AdjList(int V);
    int getV() override;
    void addEdge(int u, int v, int weight) override;
    bool hasEdge(int u, int v) override;
    std::vector<Edge> getNeighbors(int u) override;
};

#endif