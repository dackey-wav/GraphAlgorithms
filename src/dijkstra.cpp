#include "dijkstra.h"
#include "graph.h"
#include <algorithm>
#include <queue>
#include <climits>

std::pair<std::vector<int>, std::vector<int>> dijkstra(const GraphArray& graph, int start, int vertexCount) {
    std::vector<int> dist(vertexCount, INT_MAX); //wektor o długości vertexCount wypełniony "nieskonczonościami" (odległość nieznana). odległość od start do i
    std::vector<int> prev(vertexCount, -1); // wektor o długości vertexCount wypełniony -1 (ścieżka nie znaleziona). poprzedni wierszchołek (z którego przyszliśmy)
    dist[start] = 0;

    using kp = std::pair<int, int>; // {distance, vertex}
    std::priority_queue<kp, std::vector<kp>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (const auto& [v, weight] : graph.getNeighbors(u)) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    return {dist, prev};
}

std::vector<int> pathBuild(int start, int target, const std::vector<int>& prev) {
    std::vector<int> path;
    for (int a = target; a != -1; a = prev[a]) {
        path.push_back(a);
    }

    std::reverse(path.begin(), path.end());

    if (path.front() != start) {
        return {};
    }
    
    return path;
}