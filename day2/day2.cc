#include <iostream>
#include <chrono>
#include "graph.h"
#include "dfs.h"

using namespace std;
using namespace std::chrono;

void run_experiment(string name, Graph* g, int V) {
    DFSAnalyzer analyzer;
    auto start = high_resolution_clock::now();
    DFSResult res = analyzer.countConnectedComponents(g, V);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    cout << "=== Experiment: " << name << " ===" << endl;
    cout << "Vertices: " << V << endl;
    cout << "Components Found: " << res.numComponents << endl;
    cout << "Max Recursion Depth: " << res.maxDepth << endl;
    cout << "Edges Examined: " << res.totalEdgesExamined << endl;
    cout << "Execution Time: " << duration << " us" << endl << endl;
}

int main() {
    // 1. THE CHAIN: Highly recursive
    int V_chain = 5000;
    AdjList chainGraph(V_chain);
    for(int i = 0; i < V_chain - 1; ++i) {
        chainGraph.addEdge(i, i+1, 1);
        chainGraph.addEdge(i+1, i, 1);
    }
    run_experiment("The Chain (Deep Recursion)", &chainGraph, V_chain);

    // 2. THE FOREST: Many small components
    int V_forest = 5000;
    AdjList forestGraph(V_forest);
    for(int i = 0; i < V_forest; i += 2) {
        if (i + 1 < V_forest) {
            forestGraph.addEdge(i, i+1, 1);
            forestGraph.addEdge(i+1, i, 1);
        }
    }
    run_experiment("The Forest (Shallow Recursion)", &forestGraph, V_forest);

    return 0;
}