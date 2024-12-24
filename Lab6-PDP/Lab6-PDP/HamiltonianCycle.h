#pragma once
#include <vector>
#include <atomic>
#include <mutex>
class HamiltonianCycle
{
	private:
        const std::vector<std::vector<int>>& graph;
        int startingNode;
        std::atomic<bool>& foundHamiltonianCycle;
        std::vector<int> possiblePath;
        std::vector<int>& output;
        std::vector<bool> visited;
        void foundCycle();
        void goToNode(int nextNode,int depth);

public:
    HamiltonianCycle(const std::vector<std::vector<int>>& graph, int startingNode,
        std::atomic<bool>& foundHamiltonianCycle, std::vector<int>& output);

    void operator()();
};

