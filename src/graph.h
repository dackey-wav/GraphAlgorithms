#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>

class GraphArray {
    public:
        virtual void addEdge(int u, int v, int weight = 1) = 0; // u - wierzchołek startowy, v - wierzchołek końcowy
        virtual bool isConnected(int u, int v) const = 0; 
        virtual void print() const = 0;
        virtual std::vector<std::pair<int, int>> getNeighbors(int u) const = 0;
        virtual void clear() = 0;
        virtual ~GraphArray() {}
};

class AdjacencyMatrix : public GraphArray {
    private:
        int size;
        std::vector<int> matrix;
    
    public:
        AdjacencyMatrix(int n) : size(n), matrix(n * n, 0) {}

        void addEdge(int u, int v, int weight = 1) override {
            matrix[u * size + v] = weight;
        }
    
        bool isConnected(int u, int v) const override {
            return matrix[u * size + v] != 0;
        }
    
        void print() const override {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << matrix[i * size + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        std::vector<std::pair<int, int>> getNeighbors(int u) const override {
            std::vector<std::pair<int, int>> neighbors;
            for (int v = 0; v < size; ++v) {
                int weight = matrix[u * size + v];
                if (weight != 0) {
                    neighbors.emplace_back(v, weight);
                }
            }
            return neighbors;
        }
        
        void clear() override {
            std::fill(matrix.begin(), matrix.end(), 0);
        }
    };
    
class AdjacencyLists : public GraphArray {
    private:
        std::vector<std::vector<std::pair<int, int>>> lists;

    public:
        AdjacencyLists(int n) : lists(n) {}

        void addEdge(int u, int v, int weight = 1) override {
            lists[u].emplace_back(v, weight);
        }
        
        bool isConnected(int u, int v) const override {
            for (const auto& pair : lists[u]) {
                if (pair.first == v) return true;
            }
            return false;
        }

        void print() const override {
            for(int i = 0; i < lists.size(); ++i) {
                std::cout << i << ": ";
                for(const auto &pair : lists[i]) {
                    std::cout << "(" << pair.first << ", w=" << pair.second << ") ";
                }
                std::cout << std::endl;
            }
        }

        std::vector<std::pair<int, int>> getNeighbors(int u) const override {
            return lists[u];
        }

        void clear() override {
            for (auto& neighbors : lists) {
                neighbors.clear();
            }
        }
};
#endif
