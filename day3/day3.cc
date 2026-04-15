#include <iostream>
#include <chrono>
#include "../day1/graph.h"
#include "bfs.h"

using namespace std;
using namespace std::chrono;

void run_experiment(string name, Graph* g, int V, int start) {
    BFSAnalyzer analyzer;
    auto start_t = high_resolution_clock::now();
    BFSResult res = analyzer.solve(g, V, start);
    auto end_t = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end_t - start_t).count();

    cout << "=== Experiment: " << name << " ===" << endl;
    cout << "Vertices: " << V << endl;
    cout << "Max Distance Found: " << res.maxDistance << endl;
    cout << "Peak Queue Size (Memory): " << res.maxQueueSize << endl;
    cout << "Execution Time: " << duration << " us" << endl << endl;
}

int main() {
    int V = 10000;

    // 1. THE CHAIN: Linear structure (BFS explores one node per layer)
    AdjList chain(V);
    for(int i = 0; i < V - 1; ++i) {
        chain.addEdge(i, i+1, 1);
        chain.addEdge(i+1, i, 1);
    }
    run_experiment("The Chain (Linear)", &chain, V, 0);

    // 2. THE STAR: Hub structure (BFS explores all nodes in one giant layer)
    AdjList star(V);
    for(int i = 1; i < V; ++i) {
        star.addEdge(0, i, 1);
        star.addEdge(i, 0, 1);
    }
    run_experiment("The Star (Hub)", &star, V, 0);

    return 0;
}