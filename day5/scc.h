#ifndef SCC_H
#define SCC_H

#include "../day1/graph.h"
#include <vector>
#include <stack>

struct SCCResult {
    int componentCount;
    long edgeExaminations;
    long dfsCalls;
    size_t estimatedMemoryBytes;
    std::string method;
};

class SCCAnalyzer {
public:
    SCCResult runKosaraju(Graph* g, int V);
    SCCResult runTarjan(Graph* g, int V);

private:
    // Kosaraju Helpers
    void fillOrder(Graph* g, int v, std::vector<bool>& visited, std::stack<int>& s, long& edges, long& calls);
    void DFS_Transpose(AdjList& transpose, int v, std::vector<bool>& visited, long& edges, long& calls);

    // Tarjan Helpers
    void tarjanDFS(Graph* g, int u, std::vector<int>& disc, std::vector<int>& low, 
                   std::stack<int>& st, std::vector<bool>& stackMember, 
                   int& time, int& count, long& edges, long& calls);
};

#endif