#include <iostream>
#include <cassert>
#include "../day1/graph.h"
#include "toposort.h"

using namespace std;

int main() {
    int V = 6;
    AdjList g(V);
    TopoAnalyzer analyzer;

    // Student Task: Model a "Course Prerequisite" graph
    // Example: CS101 -> CS202 -> CS349
    g.addEdge(0, 1, 1); // 0 must come before 1
    g.addEdge(1, 2, 1); // 1 must come before 2
    g.addEdge(3, 1, 1); // 3 must come before 1
    g.addEdge(4, 5, 1); // 4 must come before 5

    TopoResult res = analyzer.kahnSort(&g, V);

    cout << "Topological Order (Kahn's): ";
    if (!res.isDAG) {
        cout << "unidentified (Cycle Detected!)" << endl;
    } else {
        for (int v : res.order) cout << v << " ";
        cout << endl;
    }

    assert(res.isDAG == true);
    cout << "Toposort Logic Verified!" << endl;
    return 0;
}