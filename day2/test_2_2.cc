#include <iostream>
#include <cassert>
#include "graph.h"
#include "dfs.h"

int main() {
    int V = 7;
    AdjList g(V);
    DFSAnalyzer analyzer;

    // Component 1: A triangle (0-1-2)
    g.addEdge(0, 1, 1); g.addEdge(1, 0, 1);
    g.addEdge(1, 2, 1); g.addEdge(2, 1, 1);
    g.addEdge(2, 0, 1); g.addEdge(0, 2, 1);

    // Component 2: A line (3-4)
    g.addEdge(3, 4, 1); g.addEdge(4, 3, 1);

    // Component 3: Isolated nodes (5) and (6)
    
    DFSResult res = analyzer.countConnectedComponents(&g, V);

    std::cout << "Detected Components: " << res.numComponents << " (Expected: 4)" << std::endl;
    assert(res.numComponents == 4);
    
    std::cout << "DFS Logic Verified!" << std::endl;
    return 0;
}