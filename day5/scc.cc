#include "scc.h"
#include <algorithm>

// --- KOSARAJU ---
void SCCAnalyzer::fillOrder(Graph* g, int v, std::vector<bool>& visited, std::stack<int>& s, long& edges, long& calls) {
    visited[v] = true;
    calls++;
    for (auto& edge : g->getNeighbors(v)) {
        edges++;
        if (!visited[edge.to]) fillOrder(g, edge.to, visited, s, edges, calls);
    }
    s.push(v);
}

void SCCAnalyzer::DFS_Transpose(AdjList& transpose, int v, std::vector<bool>& visited, long& edges, long& calls) {
    visited[v] = true;
    calls++;
    for (auto& edge : transpose.getNeighbors(v)) {
        edges++;
        if (!visited[edge.to]) DFS_Transpose(transpose, edge.to, visited, edges, calls);
    }
}

SCCResult SCCAnalyzer::runKosaraju(Graph* g, int V) {
    std::stack<int> s;
    std::vector<bool> visited(V, false);
    long edges = 0, calls = 0;

    // 1. Finishing times
    for (int i = 0; i < V; i++) 
        if (!visited[i]) fillOrder(g, i, visited, s, edges, calls);

    // 2. Transpose
    AdjList transpose(V);
    long transpose_edges = 0;
    for (int i = 0; i < V; i++) {
        for (auto& edge : g->getNeighbors(i)) {
            transpose.addEdge(edge.to, i, edge.weight);
            transpose_edges++;
        }
    }

    // 3. Second DFS
    std::fill(visited.begin(), visited.end(), false);
    int count = 0;
    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (!visited[v]) {
            count++;
            DFS_Transpose(transpose, v, visited, edges, calls);
        }
    }

    // Memory: Original Graph + Transpose Graph + visited + stack
    size_t mem = (V * sizeof(void*) + transpose_edges * sizeof(Edge)) + (V * sizeof(bool));
    return {count, edges, calls, mem, "Kosaraju"};
}

// --- TARJAN ---
void SCCAnalyzer::tarjanDFS(Graph* g, int u, std::vector<int>& disc, std::vector<int>& low, 
                             std::stack<int>& st, std::vector<bool>& stackMember, 
                             int& time, int& count, long& edges, long& calls) {
    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;
    calls++;

    for (auto& edge : g->getNeighbors(u)) {
        edges++;
        int v = edge.to;
        if (disc[v] == -1) {
            tarjanDFS(g, v, disc, low, st, stackMember, time, count, edges, calls);
            low[u] = std::min(low[u], low[v]);
        } else if (stackMember[v]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        count++;
        while (true) {
            int v = st.top();
            st.pop();
            stackMember[v] = false;
            if (u == v) break;
        }
    }
}

SCCResult SCCAnalyzer::runTarjan(Graph* g, int V) {
    std::vector<int> disc(V, -1), low(V, -1);
    std::vector<bool> stackMember(V, false);
    std::stack<int> st;
    int time = 0, count = 0;
    long edges = 0, calls = 0;

    for (int i = 0; i < V; i++)
        if (disc[i] == -1) tarjanDFS(g, i, disc, low, st, stackMember, time, count, edges, calls);

    // Memory: Disc, Low, stackMember, stack (max V)
    size_t mem = V * (sizeof(int) * 2 + sizeof(bool) + sizeof(int));
    return {count, edges, calls, mem, "Tarjan"};
}