#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "graph.h"

using namespace std;
using namespace std::chrono;

void measure_performance(Graph* g, int V, int E, string label) {
    auto start = high_resolution_clock::now();

    // 1. Measure Edge Addition
    for (int i = 0; i < E; ++i) {
        g->addEdge(i % V, (i * 13) % V, 1);
    }
    auto mid = high_resolution_clock::now();

    // 2. Measure Edge Removal
    for (int i = 0; i < E; ++i) {
        g->removeEdge(i % V, (i * 13) % V);
    }
    auto end = high_resolution_clock::now();

    auto add_time = duration_cast<microseconds>(mid - start).count();
    auto rem_time = duration_cast<microseconds>(end - mid).count();

    cout << "=== " << label << " ===" << endl;
    cout << "Add " << E << " edges:    " << add_time << " us" << endl;
    cout << "Remove " << E << " edges: " << rem_time << " us" << endl;
    
    // Space Estimation (Calculated based on standard C++ overhead)
    if (label == "AdjMatrix") {
        long bytes = (long)V * V * sizeof(int);
        cout << "Est. Space Usage: " << bytes / 1024 << " KB" << endl;
    } else {
        // V pointers + E Edge structs
        long bytes = (V * sizeof(void*)) + (E * sizeof(Edge));
        cout << "Est. Space Usage: " << bytes / 1024 << " KB" << endl;
    }
    cout << endl;
}

int main() {
    // Simulation parameters: Sparse Graph
    int V = 5000;  
    int E = 10000; 

    cout << "Starting Graph Stress Test (V=" << V << ", E=" << E << ")..." << endl << endl;

    AdjMatrix m(V);
    AdjList l(V);

    measure_performance(&m, V, E, "AdjMatrix");
    measure_performance(&l, V, E, "AdjList");

    return 0;
}