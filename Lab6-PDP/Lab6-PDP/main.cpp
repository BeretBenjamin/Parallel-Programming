#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <random>
#include <functional>
#include <chrono>
#include <iostream>
#include "HamiltonianCycle.h"

const int THREAD_COUNT = 5;

std::vector<std::vector<int>> generateRandomGraph(int nrVertices, int nrEdges) {
    if (nrVertices * (nrVertices - 1) < nrEdges) {
        throw std::invalid_argument("Invalid number of edges for the graph!");
    }

    std::vector<std::vector<int>> graph(nrVertices);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dist(0, nrVertices - 1);

    int index = 0;
    while (index < nrEdges) {
        int nodeA = dist(gen);
        int nodeB = dist(gen);

        if (nodeA != nodeB &&
            std::find(graph[nodeA].begin(), graph[nodeA].end(), nodeB) == graph[nodeA].end()) {
            graph[nodeA].push_back(nodeB);
            index++;
        }
    }

    return graph;
}

std::vector<std::vector<int>> loadGraph(const std::string& path) {
    std::ifstream infile(path);
    if (!infile.is_open()) {
        throw std::runtime_error("File not found: " + path);
    }

    std::vector<std::vector<int>> graph;
    std::string line;

    if (std::getline(infile, line)) {
        int size = std::stoi(line);
        graph.resize(size);
    }

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int nodeA, nodeB;
        iss >> nodeA >> nodeB;
        graph[nodeA].push_back(nodeB);
    }

    infile.close();
    return graph;
}


int main() {
    try {
        
        //auto graph = loadGraph("g1.txt");
        auto graph = generateRandomGraph(5, 10);
        std::cout << "Graph:" << std::endl;
        for (size_t i = 0; i < graph.size(); ++i) {
            std::cout << i << ": ";
            for (int neighbor : graph[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }

        std::atomic<bool> foundHamiltonianCycle(false);
        std::vector<int> output;

        std::vector<std::thread> threads;
        for (int i = 0; i < THREAD_COUNT; ++i) {
            threads.emplace_back(HamiltonianCycle(graph, i, foundHamiltonianCycle, output));
        }

        for (auto& thread : threads) {
            thread.join();
        }

        if (foundHamiltonianCycle.load()) {
            std::cout << "Hamiltonian Cycle found: ";
            for (int node : output) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "No Hamiltonian cycles found" << std::endl;
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
