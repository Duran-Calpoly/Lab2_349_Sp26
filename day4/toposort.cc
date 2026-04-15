#include "toposort.h"
#include <queue>
#include <algorithm>

TopoResult TopoAnalyzer::kahnSort(Graph* g, int V) {
    std::vector<int> inDegree(V, 0);
    for (int i = 0; i < V; ++i) {
        for (auto& edge : g->getNeighbors(i)) {
            inDegree[edge.to]++;
        }
    }

    std::queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (inDegree[i] == 0) q.push(i);
    }

    std::vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);

        for (auto& edge : g->getNeighbors(u)) {
            inDegree[edge.to]--;
            if (inDegree[edge.to] == 0) q.push(edge.to);
        }
    }

    bool isDAG = (result.size() == (size_t)V);
    return {result, isDAG, "Kahn's"};
}

TopoResult TopoAnalyzer::dfsSort(Graph* g, int V) {
    std::vector<bool> visited(V, false);
    std::vector<bool> onStack(V, false);
    std::vector<int> result;
    bool hasCycle = false;

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs_helper(g, i, visited, onStack, result, hasCycle);
        }
    }

    std::reverse(result.begin(), result.end());
    return {result, !hasCycle, "DFS-based"};
}

void TopoAnalyzer::dfs_helper(Graph* g, int v, std::vector<bool>& visited, std::vector<bool>& onStack, std::vector<int>& result, bool& hasCycle) {
    visited[v] = true;
    onStack[v] = true;

    for (auto& edge : g->getNeighbors(v)) {
        if (onStack[edge.to]) hasCycle = true;
        if (!visited[edge.to]) {
            dfs_helper(g, edge.to, visited, onStack, result, hasCycle);
        }
    }

    onStack[v] = false;
    result.push_back(v);
}