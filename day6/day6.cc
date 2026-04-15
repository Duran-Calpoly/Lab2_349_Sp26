#include <iostream>
#include <chrono>
#include "graph.h"
#include "dijkstra.h"

using namespace std;
using namespace std::chrono;

void measure(string label, Graph* g, int V) {
    DijkstraAnalyzer analyzer;
    auto s = high_resolution_clock::now();
    DijkstraResult r = analyzer.solve(g, V, 0);
    auto e = high_resolution_clock::now();

    cout << "=== " << label << " ===" << endl;
    cout << "Time: " << duration_cast<microseconds>(e-s).count() << " us" << endl;
    cout << "Relaxations: " << r.relaxations << endl;
    cout << "Max PQ Size: " << r.maxPQSize << endl << endl;
}

int main() {
    int V = 5000;
    AdjList sparse(V);
    for(int i = 0; i < V-1; i++) sparse.addEdge(i, i+1, 2);

    AdjList dense(V);
    for(int i = 0; i < V; i++) {
        for(int j = i+1; j < i+20; j++) { // Each node connected to next 20
            if (j < V) dense.addEdge(i, j, 5);
        }
    }

    measure("Sparse Graph (Line)", &sparse, V);
    measure("Dense Graph (Multi-connected)", &dense, V);

    return 0;
}