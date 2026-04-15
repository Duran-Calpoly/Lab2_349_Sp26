#include <iostream>
#include <chrono>
#include <iomanip>
#include "../day1/graph.h"
#include "scc.h"

using namespace std;
using namespace std::chrono;

void print_res(SCCResult r, long duration) {
    cout << left << setw(12) << r.method 
         << " | Time: " << setw(8) << duration << "us"
         << " | Edges: " << setw(8) << r.edgeExaminations 
         << " | Mem: ~" << r.estimatedMemoryBytes / 1024 << "KB" << endl;
}

int main() {
    int V = 5000;
    AdjList ring(V);
    for(int i = 0; i < V; i++) ring.addEdge(i, (i+1)%V, 1);

    cout << "Experiment 1: Giant Ring (1 SCC, V=" << V << ")" << endl;
    SCCAnalyzer analyzer;
    
    auto s1 = high_resolution_clock::now();
    auto rK = analyzer.runKosaraju(&ring, V);
    auto e1 = high_resolution_clock::now();
    print_res(rK, duration_cast<microseconds>(e1-s1).count());

    auto s2 = high_resolution_clock::now();
    auto rT = analyzer.runTarjan(&ring, V);
    auto e2 = high_resolution_clock::now();
    print_res(rT, duration_cast<microseconds>(e2-s2).count());

    return 0;
}