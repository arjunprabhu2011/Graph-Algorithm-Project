#include "Graph.h"

Graph::Graph(int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        vector<int> vec;
        adjLists.push_back(vec);
    }
}

void Graph::addNode(Node node) {
    nodes.push_back(node);
    
    for (size_t i = 0; i < nodes.size() - 1; i++) {
        vector<string> vec1(node.getProductIDs());
        vector<string> vec2(nodes[i].getProductIDs());

        //Check for intersections in the product vector between 2 nodes
        //If an intersection exists, add an edge between the 2 nodes
        vector<string> intersections(std::max(vec1.size(), vec2.size()));

        sort(vec1.begin(), vec1.end());
        sort(vec2.begin(), vec2.end());
        vector<string>::iterator end;
        end = set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), intersections.begin());
        if (intersections.begin() != end) {
            addEdge(i, nodes.size() - 1);
        }
    }
}

void Graph::addEdge(size_t index_source, size_t index_destination) {
    adjLists[index_source].push_back(index_destination);
    adjLists[index_destination].push_back(index_source);
}

double Graph::calculateEdgeWeight(Node node1, Node node2) {
    vector<string> vec1(node1.getProductIDs());
    vector<string> vec2(node2.getProductIDs());
    vector<string> intersections(std::max(vec1.size(), vec2.size()));

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    vector<string>::iterator end;
    end = set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), intersections.begin());
    //Find the number of common values between the two nodes' product vectors, and do 1/common_values
    
    double common_values = 0;
    vector<string>::iterator it = intersections.begin();
    while(it != end) {
        common_values++;
        it++;
    }

    if (common_values == 0) {
        return 100000000;
    }

    return 1.0/common_values;
}

vector<Node> Graph::getNodes() {
    return nodes;
}

vector<vector<int>> Graph::getAdjLists() {
    return adjLists;
}