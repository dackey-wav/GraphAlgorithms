#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <utility>

class GraphArray;

std::pair<std::vector<int>, std::vector<int>> dijkstra(const GraphArray& graph, int start, int vertexCount);
std::vector<int> pathBuild(int start, int target, const std::vector<int>& prev);

#endif