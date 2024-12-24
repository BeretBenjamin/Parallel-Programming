#include "HamiltonianCycle.h"
#include <algorithm>
const int MAX_DEPTH = 5;

HamiltonianCycle::HamiltonianCycle(const std::vector<std::vector<int>>& graph, int startingNode,
    std::atomic<bool>& foundHamiltonianCycle, std::vector<int>& output)
    : graph(graph), startingNode(startingNode), foundHamiltonianCycle(foundHamiltonianCycle), output(output) {
    visited.resize(graph.size(), false);
}

void HamiltonianCycle::foundCycle() {
    possiblePath.push_back(startingNode);
    foundHamiltonianCycle = true;
    output = possiblePath;
}

void HamiltonianCycle::goToNode(int nextNode,int depth) {
    if (foundHamiltonianCycle) return;

    possiblePath.push_back(nextNode);
    visited[nextNode] = true;

    if (possiblePath.size() == graph.size() &&
        std::find(graph[nextNode].begin(), graph[nextNode].end(), startingNode) != graph[nextNode].end()) {
        foundCycle();
    }
    else {
        if (depth < MAX_DEPTH)
        {
        std::vector<std::thread> threads;
        for (int neighbor : graph[nextNode]) {
            if (!visited[neighbor]) {
                threads.emplace_back([this, neighbor,depth]() {
                    auto newPath = possiblePath;       
                    auto newVisited = visited;        
                    HamiltonianCycle task(graph, startingNode, foundHamiltonianCycle, output);
                    task.possiblePath = std::move(newPath);
                    task.visited = std::move(newVisited);
                    task.goToNode(neighbor,depth+1);
                    //return;
                    });
                
            }
        }
        for (auto& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        }
        else {
            for (int neighbor : graph[nextNode])
            {
                if (!visited[neighbor])
                {
                    goToNode(neighbor, depth + 1);
                    return;
                }
            }

        }
        
    }

    visited[nextNode] = false;
    possiblePath.pop_back();
}

void HamiltonianCycle::operator()() {
    goToNode(startingNode,0);
}
