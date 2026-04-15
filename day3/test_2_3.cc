#include <iostream>
#include <cassert>
#include <string>
#include "../day1/graph.h"
#include "bfs.h"

using namespace std;

int main() {
    int V = 8;
    AdjList g(V);
    BFSAnalyzer analyzer;

    // Student Task: Construct a graph with competing paths
    g.addEdge(0, 1, 1); g.addEdge(1, 0, 1);
    g.addEdge(1, 2, 1); g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 1); g.addEdge(3, 2, 1);
    g.addEdge(0, 4, 1); g.addEdge(4, 0, 1);
    g.addEdge(4, 3, 1); g.addEdge(3, 4, 1);

    BFSResult res = analyzer.solve(&g, V, 0);

    // If a node distance is -1, we label it "unidentified"
    string dist_str = (res.distances[3] == -1) ? "unidentified" : to_string(res.distances[3]);
    
    cout << "Shortest distance from 0 to 3: " << dist_str << " (Expected: 2)" << endl;
    assert(res.distances[3] == 2);

    cout << "BFS Shortest Path Logic Verified!" << endl;
    return 0;
}