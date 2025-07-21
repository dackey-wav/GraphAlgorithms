#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <random>
#include <iomanip>
#include <set>
#include <numeric>
#include "src\graph.h"
#include "src\dijkstra.h"
#include "src\bellmanFord.h"
#include "src\dfs.h"

using namespace std::chrono;

void generateEdges(GraphArray& graph, int vertexCount, int edgeCount, int maxWeight = 10, bool allowNegative = false) {
    std::vector<int> edges(vertexCount);
    std::iota(edges.begin(), edges.end(), 0);

    std::random_device rd; // seed
    std::mt19937 gen(rd()); // generator liczb
    shuffle(edges.begin(), edges.end(), gen);

    std::vector<std::pair<int, int>> possibleEdges;

    for (int i = 0; i < vertexCount; ++i) {
        for (int j = i + 1; j < vertexCount; ++j) {
            possibleEdges.emplace_back(edges[i], edges[j]);
        }
    }

    shuffle(possibleEdges.begin(), possibleEdges.end(), gen);
    std::uniform_int_distribution<> weightDist(allowNegative ? -maxWeight : 1, maxWeight);

    int added = 0;
    for (const auto& [u, v] : possibleEdges) {
        if (added >= edgeCount) break;

        int weight;
        do {
            weight = weightDist(gen);
        } while (weight == 0);

        graph.addEdge(u, v, weight);
        added++;
    }
}


// Dijkstra, B-F 
void runTest(std::ofstream& out, int vertexCount, double density, bool useMatrix, int algorithmType) {
    int maxEdges = vertexCount * (vertexCount - 1); // maksymalna liczba krawędzi
    int edgeCount = static_cast<int>(density * maxEdges); // liczba krawędzi potrzebna zgodnie z gęstością
    double totalTime = 0.0;
    double totalPathLength = 0.0;

    for (int i = 0; i < 100; ++i) {
        std::unique_ptr<GraphArray> graph;
        if (useMatrix) graph = std::make_unique<AdjacencyMatrix>(vertexCount);
        else graph = std::make_unique<AdjacencyLists>(vertexCount);

        if (algorithmType == 0) generateEdges(*graph, vertexCount, edgeCount, 10, false);
        if (algorithmType == 1) generateEdges(*graph, vertexCount, edgeCount, 10, true);

        auto start = high_resolution_clock::now();
        if (algorithmType == 0) {
            dijkstra(*graph, 0, vertexCount);
        } else if (algorithmType == 1) {
            bellmanFord(*graph, 0, vertexCount);
        }
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;
        totalTime += elapsed.count();
    }

    double avgTime = totalTime / 100.0;
    out << vertexCount << "\t" << density << "\t" << avgTime << std::endl;
}

void runTestDFS(std::ofstream& out, int vertexCount, double density, bool useMatrix) {
    int maxEdges = vertexCount * (vertexCount - 1);
    int edgeCount = static_cast<int>(density * maxEdges);
    double totalTime = 0.0;

    for (int i = 0; i < 100; ++i) {
        std::unique_ptr<GraphArray> graph;
        if (useMatrix)
            graph = std::make_unique<AdjacencyMatrix>(vertexCount);
        else
            graph = std::make_unique<AdjacencyLists>(vertexCount);

        generateEdges(*graph, vertexCount, edgeCount);

        auto start = high_resolution_clock::now();
        std::vector<bool> visited(vertexCount, false);
        dfs(*graph, 0, visited);
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;
        totalTime += elapsed.count();
    }

    double avgTime = totalTime / 100.0;
    out << vertexCount << "\t" << density << "\t" << avgTime << std::endl;
}

void printPathsAndDistances(const std::vector<int>& dist, const std::vector<int>& prev, int start) {
    std::cout << "Wierzcholek\tOdleglosc\tSciezka" << std::endl;
    for (int i = 0; i < dist.size(); ++i) {
        std::cout << i << "\t\t";
        if (dist[i] == INT_MAX) {
            std::cout << "Brak sciezki" << std::endl;
            continue;
        }
        std::cout << dist[i] << "\t\t";
        std::vector<int> path;
        for (int at = i; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());
        for (int p : path)
        std::cout << p << " ";
        std::cout << std::endl;
    }
}

void printVisitedDFS(const std::vector<bool>& visited) {
    std::cout << "Odwiedzone wierzcholki: ";
    for (int i = 0; i < visited.size(); ++i) {
        if (visited[i])
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    try {
        // Test na małym grafie
        int vertexCount = 6;
        AdjacencyLists testGraph(vertexCount);
        AdjacencyLists testGraphBF(vertexCount);

        testGraph.addEdge(0, 1, 7);
        testGraph.addEdge(0, 2, 9);
        testGraph.addEdge(0, 5, 14);
        testGraph.addEdge(1, 2, 10);
        testGraph.addEdge(1, 3, 15);
        testGraph.addEdge(2, 3, 11);
        testGraph.addEdge(2, 5, 2);
        testGraph.addEdge(3, 4, 6);
        testGraph.addEdge(4, 5, 9);

        // z ujemnymi wagami dla B-F 
        testGraphBF.addEdge(0, 1, 5);
        testGraphBF.addEdge(1, 3, 3);
        testGraphBF.addEdge(1, 4, 9);
        testGraphBF.addEdge(3, 4, 3);
        testGraphBF.addEdge(3, 5, 2);
        testGraphBF.addEdge(4, 2, -1);
        testGraphBF.addEdge(4, 5, -5);
        testGraphBF.addEdge(5, 2, 8);
        testGraphBF.addEdge(5, 0, 9);
        testGraphBF.addEdge(2, 1, -4);
        testGraphBF.addEdge(2, 0, 3);

        auto [distDijkstra, prevDijkstra] = dijkstra(testGraph, 0, vertexCount);
        std::cout << "\n______Dijkstra______" << std::endl;
        printPathsAndDistances(distDijkstra, prevDijkstra, 0);

        try {
            auto [distBellman, prevBellman] = bellmanFord(testGraphBF, 0, vertexCount);
            std::cout << "\n______B-F______" << std::endl;
            printPathsAndDistances(distBellman, prevBellman, 0);
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        std::vector<bool> visited(vertexCount, false);
        dfs(testGraph, 0, visited);
        std::cout << "\n______DFS______" << std::endl;
        printVisitedDFS(visited);



        //graphviz
        std::cout << "\n\ndigraph G {" << std::endl;
        for (int u = 0; u < vertexCount; ++u) {
            for (const auto& [v, weight] : testGraph.getNeighbors(u)) {
                std::cout << "\t" << u << " -> " << v << " [label=\"" << weight << "\"];" << std::endl;
            }
        }
        std::cout << "}\n\n";

        std::cout << "\n\ndigraph G {" << std::endl;
        for (int u = 0; u < vertexCount; ++u) {
            for (const auto& [v, weight] : testGraphBF.getNeighbors(u)) {
                std::cout << "\t" << u << " -> " << v << " [label=\"" << weight << "\"];" << std::endl;
            }
        }
        std::cout << "}\n\n";

        
        // testy
        std::ofstream outputMatrixDijkstra("results\\matrix_dijkstra.txt");
        if (!outputMatrixDijkstra.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }
        std::ofstream outputMatrixBellman("results\\matrix_bellman.txt");
        if (!outputMatrixBellman.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }
        std::ofstream outputMatrixDFS("results\\matrix_DFS.txt");
        if (!outputMatrixDFS.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }
        std::ofstream outputListDijkstra("results\\list_dijkstra.txt");
        if (!outputListDijkstra.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }
        std::ofstream outputListBellman("results\\list_bellman.txt");
        if (!outputListBellman.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }
        std::ofstream outputListDFS("results\\list_DFS.txt");
        if (!outputListDFS.is_open()) {
            std::cerr << "Nie udalo sie odtworzyc pliku" << std::endl;
            return 1;
        }

        outputMatrixDijkstra << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;
        outputMatrixBellman << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;
        outputMatrixDFS << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;
        outputListDijkstra << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;
        outputListBellman << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;
        outputListDFS << "Liczba wierzchołków" << "\t" << "Gęstość" << "\t" << "Czas(s)" << std::endl;

        std::vector<int> vertexCounts = {10, 50, 100, 200, 500};
        std::vector<double> densities = {0.25, 0.5, 1.0};

        for (int v : vertexCounts) {
            for (double d : densities) {
                try {
                    runTest(outputMatrixDijkstra, v, d, true, 0);
                } catch (const std::exception& e) {
                    std::cout << "Error Dijkstra Matrix: " << e.what() << std::endl;
                }
                try {
                    runTest(outputMatrixBellman, v, d, true, 1);
                } catch (const std::exception& e) {
                    std::cout << "Error B-F Matrix: " << e.what() << std::endl;
                }
                try {
                    runTestDFS(outputMatrixDFS, v, d, true);
                } catch (const std::exception& e) {
                    std::cout << "Error DFS Matrix: " << e.what() << std::endl;
                }
                try {
                    runTest(outputListDijkstra, v, d, false, 0);
                } catch (const std::exception& e) {
                    std::cout << "Error Dijkstra List: " << e.what() << std::endl;
                }
                try {
                    runTest(outputListBellman, v, d, false, 1);
                } catch (const std::exception& e) {
                    std::cout << "Error B-F List: " << e.what() << std::endl;
                }
                try {
                    runTestDFS(outputListDFS, v, d, false);
                } catch (const std::exception& e) {
                    std::cout << "Error DFS List: " << e.what() << std::endl;
                }
            }   
        }

        outputMatrixDijkstra.close();
        outputMatrixBellman.close();
        outputMatrixDFS.close();
        outputListDijkstra.close();
        outputListBellman.close();
        outputListDFS.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}