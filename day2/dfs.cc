#include "dfs.h"
#include <algorithm>

DFSAnalyzer::DFSAnalyzer() : current_depth(0), max_depth_reached(0), edges_counted(0) {}

void DFSAnalyzer::DFS_Helper(Graph* g, int v, std::vector<bool>& visited) {
    visited[v] = true;
    current_depth++;
    max_depth_reached = std::max(max_depth_reached, current_depth);

    std::vector<Edge> neighbors = g->getNeighbors(v);
    for (auto& edge : neighbors) {
        edges_counted++;
        if (!visited[edge.to]) {
            DFS_Helper(g, edge.to, visited);
        }
    }

    current_depth--; // Backtracking the stack
}

DFSResult DFSAnalyzer::countConnectedComponents(Graph* g, int V) {
    std::vector<bool> visited(V, false);
    int components = 0;
    max_depth_reached = 0;
    edges_counted = 0;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            components++;
            current_depth = 0;
            DFS_Helper(g, i, visited);
        }
    }

    return {components, max_depth_reached, edges_counted};
}