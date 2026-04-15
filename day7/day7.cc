#include <iostream>
#include <chrono>
#include "graph.h"
#include "pathfinder.h"

using namespace std;
using namespace std::chrono;

void measure(Graph* g, int start, string name) {
    PathAnalyzer analyzer;
    
    auto s1 = high_resolution_clock::now();
    auto r1 = analyzer.runBellmanFord(g, start);
    auto e1 = high_resolution_clock::now();

    auto s2 = high_resolution_clock::now();
    auto r2 = analyzer.runSPFA(g, start);
    auto e2 = high_resolution_clock::now();

    cout << "=== Experiment: " << name << " ===" << endl;
    cout << "BF Time:   " << duration_cast<microseconds>(e1-s1).count() << " us | Relaxations: " << r1.relaxations << endl;
    cout << "SPFA Time: " << duration_cast<microseconds>(e2-s2).count() << " us | Relaxations: " << r2.relaxations << endl;
    cout << "Cycle? " << (r1.hasNegativeCycle ? "Yes" : "No") << endl << endl;
}

int main() {
    int V = 1000;
    AdjList safe(V);
    for(int i = 0; i < V-1; i++) safe.addEdge(i, i+1, 5);

    measure(&safe, 0, "Sparse Linear Graph");

    return 0;
}