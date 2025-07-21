#ifndef DFS_H
#define DFS_H

#include <vector>
#include "graph.h"

class GraphArray;

void dfs(const GraphArray& graph, int u, std::vector<bool>& visited);

void fullDFS(const GraphArray& graph, int start, int vertexCount);

#endif