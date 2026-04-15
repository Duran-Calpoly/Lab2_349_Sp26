#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <vector>

struct DFSResult {
    int numComponents;
    int maxDepth;
    long totalEdgesExamined;
};

class DFSAnalyzer {
private:
    int current_depth;
    int max_depth_reached;
    long edges_counted;

    void DFS_Helper(Graph* g, int v, std::vector<bool>& visited);

public:
    DFSAnalyzer();
    DFSResult countConnectedComponents(Graph* g, int V);
};

#endif