#include <iostream>
#include <cassert>
#include "graph.h"
#include "dijkstra.h"

using namespace std;

int main() {
    int V = 5;
    AdjList g(V);
    DijkstraAnalyzer analyzer;

    // TODO: Create a scenario where a 2-hop path is cheaper than a 1-hop path
    g.addEdge(0, 1, 100); // Expensive direct route
    g.addEdge(0, 2, 10);  // Cheap detour start
    g.addEdge(2, 1, 10);  // Cheap detour end

    DijkstraResult res = analyzer.solve(&g, V, 0);

    cout << "Shortest path from 0 to 1: " << res.distances[1] << " (Expected: 20)" << endl;
    assert(res.distances[1] == 20);

    cout << "Dijkstra Logic Verified!" << endl;
    return 0;
}