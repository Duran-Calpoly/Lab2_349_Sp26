#ifndef TOPOSORT_H
#define TOPOSORT_H

#include "../day1/graph.h"
#include <vector>
#include <string>

struct TopoResult {
    std::vector<int> order;
    bool isDAG;
    std::string method;
};

class TopoAnalyzer {
public:
    TopoResult kahnSort(Graph* g, int V);
    TopoResult dfsSort(Graph* g, int V);
private:
    void dfs_helper(Graph* g, int v, std::vector<bool>& visited, std::vector<bool>& onStack, std::vector<int>& result, bool& hasCycle);
};

#endif