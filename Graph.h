#pragma once

#include "Node.h"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <unordered_map>

using std::vector;
using std::string;
using std::set_intersection;
using std::sort;
using std::queue;
using std::unordered_map;

/**
* Class Representing the Graph itself containing nodes and edges to connect the nodes
*/
class Graph {
    public:
        Graph(int numNodes);
        void addNode(Node node);
        vector<Node> getNodes();
        vector<vector<int>> getAdjLists();
        double calculateEdgeWeight(Node node1, Node node2);

    private:
        void addEdge(size_t index_source, size_t index_destination);
        
        vector<vector<int>> adjLists;
        vector<Node> nodes;
};