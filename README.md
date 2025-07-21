# Graph Algorithm Performance Analysis

This project implements and analyzes the performance of three fundamental graph algorithms: **Dijkstra's Algorithm**, **Bellman-Ford Algorithm**, and **Depth-First Search (DFS)**. The goal is to provide a comprehensive comparison of their efficiency under various graph conditions, including different sizes, representations, and densities.

---

## Features

* **Algorithm Implementations:**
    * **Dijkstra's Algorithm:** A single-source shortest path algorithm for graphs with non-negative edge weights.
    * **Bellman-Ford Algorithm:** A single-source shortest path algorithm that handles graphs with negative edge weights.
    * **Depth-First Search (DFS):** A graph traversal algorithm that explores as far as possible along each branch before backtracking.

* **Extensive Performance Testing:**
    The project includes a robust testing framework to measure the execution time of each algorithm across a range of graph characteristics.

    * **Graph Sizes (Number of Vertices):** Measurements were taken for graphs with the following number of vertices:
        * 10
        * 50
        * 100
        * 200
        * 500

    * **Graph Representations:** Performance was evaluated using two common graph representations:
        1.  **Adjacency Matrix:** A 2D array representing connections between vertices.
        2.  **Adjacency List:** An array of lists where each list stores the neighbors of a vertex.

    * **Graph Densities:** For each graph size and representation, performance was assessed under various graph densities:
        * 25% Density
        * 50% Density
        * 75% Density
        * Complete Graph (100% Density)

    * **Averaged Results:** To ensure accuracy and reduce statistical noise, **100 measurements** were performed for each combination of graph size, representation, and density, and the results were averaged.

---

## Project Structure

* `src/`: Contains the source code for the graph algorithms and the testing framework.
* `results/`: (Likely) Where the performance measurement data or generated charts/graphs are stored.
* `Sprawozdanie.md` (or similar): A report detailing the methodology, results, and analysis of the performance tests. This report will be translated into English soon.

---
