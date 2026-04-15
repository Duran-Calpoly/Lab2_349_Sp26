#include <iostream>
#include <cassert>
#include "graph.h"

void testGraph(Graph* g) {
    // Construct a small test graph
    g->addEdge(0, 1, 10);
    g->addEdge(0, 2, 5);
    g->addEdge(2, 1, 3);
    
    assert(g->hasEdge(0, 1) == true);
    assert(g->hasEdge(1, 0) == false); // Directed check
    
    // Test Removal
    g->removeEdge(0, 1);
    assert(g->hasEdge(0, 1) == false);
    assert(g->getNeighbors(0).size() == 1); // Only node 2 remains
    
    std::cout << "Logic Tests Passed!" << std::endl;
}

int main() {
    std::cout << "Testing Matrix..." << std::endl;
    AdjMatrix m(5);
    testGraph(&m);

    std::cout << "Testing List..." << std::endl;
    AdjList l(5);
    testGraph(&l);

    return 0;
}