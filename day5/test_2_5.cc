#include <iostream>
#include <cassert>
#include "../day1/graph.h"
#include "scc.h"

int main() {
    int V = 5;
    AdjList g(V);
    SCCAnalyzer analyzer;

    // Create 2 SCCs: {0, 1, 2} and {3, 4}
    g.addEdge(0, 1, 1); g.addEdge(1, 2, 1); g.addEdge(2, 0, 1);
    g.addEdge(1, 3, 1); // Bridge
    g.addEdge(3, 4, 1); g.addEdge(4, 3, 1);

    SCCResult resK = analyzer.runKosaraju(&g, V);
    SCCResult resT = analyzer.runTarjan(&g, V);

    std::cout << "Kosaraju Found: " << resK.componentCount << " SCCs" << std::endl;
    std::cout << "Tarjan Found: " << resT.componentCount << " SCCs" << std::endl;

    assert(resK.componentCount == 2);
    assert(resT.componentCount == 2);

    std::cout << "SCC Logic Verified!" << std::endl;
    return 0;
}