#include <iostream>
#include <cassert>
#include "graph.h"
#include "pathfinder.h"

using namespace std;

int main() {
    int V = 4;
    AdjList g(V);
    PathAnalyzer analyzer;

    // Create a Negative Cycle: 1 -> 2 -> 3 -> 1 (Total = -1)
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 1, -5); 

    PathResult resBF = analyzer.runBellmanFord(&g, 0);
    PathResult resSPFA = analyzer.runSPFA(&g, 0);

    cout << "Bellman-Ford Negative Cycle: " << (resBF.hasNegativeCycle ? "Detected" : "Missed") << endl;
    cout << "SPFA Negative Cycle: " << (resSPFA.hasNegativeCycle ? "Detected" : "Missed") << endl;

    assert(resBF.hasNegativeCycle == true);
    assert(resSPFA.hasNegativeCycle == true);

    cout << "Negative Cycle Detection Verified!" << endl;
    return 0;
}