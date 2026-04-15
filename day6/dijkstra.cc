#include "dijkstra.h"
#include <queue>
#include <functional>

DijkstraResult DijkstraAnalyzer::solve(Graph* g, int V, int startNode) {
    std::vector<int> dists(V, -1); // -1 is unidentified
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    
    int max_pq = 0;
    long relax = 0;

    dists[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        max_pq = std::max(max_pq, (int)pq.size());
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dists[u] && dists[u] != -1) continue;

        for (auto& edge : g->getNeighbors(u)) {
            int v = edge.to;
            int weight = edge.weight;

            if (dists[v] == -1 || dists[u] + weight < dists[v]) {
                dists[v] = dists[u] + weight;
                relax++;
                pq.push({dists[v], v});
            }
        }
    }
    return {dists, relax, max_pq};
}