#include <gtest/gtest.h>
#include "../src/graph.h"
#include "../src/dijkstra.h"
#include "../src/bellmanFord.h"
#include "../src/dfs.h"

using Graph = AdjacencyMatrix;

// Dijkstra test
TEST(AlgoTest, DijkstraSimple) {
    Graph graph(3);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);

    auto result = dijkstra(graph, 0, 3);
    const auto& dist = result.first;

    ASSERT_EQ(dist[0], 0);
    ASSERT_EQ(dist[1], 3);
    ASSERT_EQ(dist[2], 1);
}

// Bellman-Ford test with negative edge
TEST(AlgoTest, BellmanFordNegativeEdge) {
    Graph graph(3);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, -2);

    auto result = bellmanFord(graph, 0, 3);
    const auto& dist = result.first;

    ASSERT_EQ(dist[0], 0);
    ASSERT_EQ(dist[1], 4);
    ASSERT_EQ(dist[2], 2);
}

// DFS test
TEST(AlgoTest, DFSSimple) {
    Graph graph(3);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);

    std::vector<bool> visited(3, false);
    dfs(graph, 0, visited);

    EXPECT_TRUE(visited[0]);
    EXPECT_TRUE(visited[1]);
    EXPECT_TRUE(visited[2]);
}