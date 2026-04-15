#include "graph.h"
#include <algorithm>

// --- Adjacency Matrix Implementation ---
AdjMatrix::AdjMatrix(int V) : V(V), matrix(V, std::vector<int>(V, 0)) {}

void AdjMatrix::addEdge(int u, int v, int weight) {
    if (u < V && v < V) matrix[u][v] = weight;
}

void AdjMatrix::removeEdge(int u, int v) {
    if (u < V && v < V) matrix[u][v] = 0;
}

bool AdjMatrix::hasEdge(int u, int v) {
    return (u < V && v < V && matrix[u][v] != 0);
}

std::vector<Edge> AdjMatrix::getNeighbors(int u) {
    std::vector<Edge> neighbors;
    if (u >= V) return neighbors;
    for (int v = 0; v < V; ++v) {
        if (matrix[u][v] != 0) neighbors.push_back({v, matrix[u][v]});
    }
    return neighbors;
}

// --- Adjacency List Implementation ---
AdjList::AdjList(int V) : V(V), list(V) {}

void AdjList::addEdge(int u, int v, int weight) {
    if (u < V) list[u].push_back({v, weight});
}

void AdjList::removeEdge(int u, int v) {
    if (u < V) {
        list[u].remove_if([v](const Edge& e) { return e.to == v; });
    }
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
    if (u >= V) return neighbors;
    for (auto const& edge : list[u]) {
        neighbors.push_back(edge);
    }
    return neighbors;
}