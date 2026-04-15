#include "pathfinder.h"
#include <queue>

const int INF = 1e9; 

PathResult PathAnalyzer::runBellmanFord(Graph* g, int startNode) {
    int V = g->getV();
    std::vector<int> dist(V, INF);
    dist[startNode] = 0;
    long relax = 0;

    // V-1 passes to relax edges
    for (int i = 1; i < V; i++) {
        bool changed = false;
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            for (auto& edge : g->getNeighbors(u)) {
                if (dist[u] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.weight;
                    relax++;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }

    // Final pass for negative cycle detection
    bool cycle = false;
    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;
        for (auto& edge : g->getNeighbors(u)) {
            if (dist[u] + edge.weight < dist[edge.to]) cycle = true;
        }
    }

    return {dist, cycle, relax, "Bellman-Ford"};
}

PathResult PathAnalyzer::runSPFA(Graph* g, int startNode) {
    int V = g->getV();
    std::vector<int> dist(V, INF);
    std::vector<int> count(V, 0);
    std::vector<bool> inQueue(V, false);
    std::queue<int> q;

    dist[startNode] = 0;
    q.push(startNode);
    inQueue[startNode] = true;
    long relax = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;

        for (auto& edge : g->getNeighbors(u)) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                relax++;
                if (!inQueue[edge.to]) {
                    q.push(edge.to);
                    inQueue[edge.to] = true;
                    count[edge.to]++;
                    if (count[edge.to] >= V) return {dist, true, relax, "SPFA"};
                }
            }
        }
    }
    return {dist, false, relax, "SPFA"};
}