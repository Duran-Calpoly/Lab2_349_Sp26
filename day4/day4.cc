#include <iostream>
#include <chrono>
#include "../day1/graph.h"
#include "toposort.h"

using namespace std;
using namespace std::chrono;

void run_experiment(Graph* g, int V, string name) {
    TopoAnalyzer analyzer;
    
    auto s1 = high_resolution_clock::now();
    TopoResult r1 = analyzer.kahnSort(g, V);
    auto e1 = high_resolution_clock::now();
    
    auto s2 = high_resolution_clock::now();
    TopoResult r2 = analyzer.dfsSort(g, V);
    auto e2 = high_resolution_clock::now();

    cout << "=== Experiment: " << name << " ===" << endl;
    cout << "Kahn's Time: " << duration_cast<microseconds>(e1 - s1).count() << " us" << endl;
    cout << "DFS-based Time: " << duration_cast<microseconds>(e2 - s2).count() << " us" << endl;
    cout << "Is DAG? " << (r1.isDAG ? "Yes" : "No (Ordering Unidentified)") << endl << endl;
}

int main() {
    int V = 5000;
    AdjList dag(V);
    for(int i = 0; i < V - 1; ++i) dag.addEdge(i, i+1, 1);
    run_experiment(&dag, V, "Long Path (DAG)");

    AdjList cycle(V);
    for(int i = 0; i < V - 1; ++i) cycle.addEdge(i, i+1, 1);
    cycle.addEdge(V-1, 0, 1); // Close the giant loop
    run_experiment(&cycle, V, "Giant Cycle");

    return 0;
}