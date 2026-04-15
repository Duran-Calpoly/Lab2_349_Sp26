#ifndef BFS_H
#define BFS_H

#include "../day1/graph.h"
#include <vector>
#include <queue>

struct BFSResult {
    std::vector<int> distances; // -1 indicates the distance is 'unidentified'
    int maxQueueSize;
    int maxDistance; 
};

class BFSAnalyzer {
public:
    BFSResult solve(Graph* g, int V, int startNode);
};

#endif