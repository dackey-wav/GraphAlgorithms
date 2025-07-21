#include "graph.h"
#include "bellmanFord.h"
#include <climits>

std::pair<std::vector<int>, std::vector<int>> bellmanFord(const GraphArray& graph, int start, int vertexCount) {
    std::vector<int> dist(vertexCount, INT_MAX);
    std::vector<int> prev(vertexCount, -1);
    dist[start] = 0;

    for (int relaxation = 0; relaxation < vertexCount - 1; ++relaxation) {
        for (int u = 0; u < vertexCount; ++u) {
            for (const auto& [v, weight] : graph.getNeighbors(u)) {
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < vertexCount; ++u) {
        for (const auto& [v, weight] : graph.getNeighbors(u)) {
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                throw std::runtime_error("Graf posiada cykl ujemny");
            }
        }
    }

    return {dist, prev};
}