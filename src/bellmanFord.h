#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include <utility>

class GraphArray;

std::pair<std::vector<int>, std::vector<int>> bellmanFord(const GraphArray& graph, int start, int vertexCount);

#endif