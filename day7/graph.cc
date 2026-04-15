#include "graph.h"

AdjList::AdjList(int V) : V(V), list(V) {}

int AdjList::getV() { 
    return V; 
}

void AdjList::addEdge(int u, int v, int weight) {
    if (u < V) list[u].push_back({v, weight});
}

bool AdjList::hasEdge(int u, int v) {
    if (u >= V) return false;
    for (auto const& edge : list[u]) {
        if (edge.to == v) return true;
    }
    return false;
}

std::vector<Edge> AdjList::getNeighbors(int u) {
    std::vector<Edge> neighbors;
    if (u < V) {
        for (auto const& edge : list[u]) {
            neighbors.push_back(edge);
        }
    }
    return neighbors;
}