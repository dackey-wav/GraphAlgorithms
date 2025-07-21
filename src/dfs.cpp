#include "dfs.h"

void dfs(const GraphArray& graph, int u, std::vector<bool>& visited) {
    visited[u] = true;
    for (const auto& [v, weight] : graph.getNeighbors(u)) {
        if (!visited[v]) {
            dfs(graph, v, visited);
        }
    }
}

void fullDFS(const GraphArray& graph, int start, int vertexCount) {
    std::vector<bool> visited(vertexCount, false);
    dfs(graph, start, visited);
}
