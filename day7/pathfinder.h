#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "graph.h" // Points to local day7/graph.h
#include <vector>
#include <string>

struct PathResult {
    std::vector<int> distances;
    bool hasNegativeCycle;
    long relaxations;
    std::string method;
};

class PathAnalyzer {
public:
    PathResult runBellmanFord(Graph* g, int startNode);
    PathResult runSPFA(Graph* g, int startNode);
};

#endif