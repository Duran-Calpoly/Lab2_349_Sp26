#include "bfs.h"
#include <algorithm>

BFSResult BFSAnalyzer::solve(Graph* g, int V, int startNode) {
    std::vector<int> dists(V, -1); // Initialize as unidentified (-1)
    std::queue<int> q;
    int peak_queue = 0;
    int peak_dist = 0;

    dists[startNode] = 0;
    q.push(startNode);

    while (!q.empty()) {
        peak_queue = std::max(peak_queue, (int)q.size());
        int u = q.front();
        q.pop();

        for (auto& edge : g->getNeighbors(u)) {
            if (dists[edge.to] == -1) { 
                dists[edge.to] = dists[u] + 1;
                peak_dist = std::max(peak_dist, dists[edge.to]);
                q.push(edge.to);
            }
        }
    }

    return {dists, peak_queue, peak_dist};
}