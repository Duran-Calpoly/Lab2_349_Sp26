#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <vector>

struct DijkstraResult {
    std::vector<int> distances;
    long relaxations; 
    int maxPQSize;
};

class DijkstraAnalyzer {
public:
    DijkstraResult solve(Graph* g, int V, int startNode);
};

#endif