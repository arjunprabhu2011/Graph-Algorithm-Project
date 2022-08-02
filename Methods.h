#include <string>

/**
* Method that traverses the Graph using a BFS Traversal
*/
vector<std::string> BFSTraversal(Graph g);

/**
* Helper Method for BFS Traversal
*/
void BFSHelper(int index, Graph graph, vector<bool>& visited, vector<std::string>& reviewers);

/**
* Method that applies Dijsktra's algorithm on the graph
*/
std::pair<vector<double>, vector<int>> Dijkstra(Graph g, int start);

/**
* Method that applies Brandes's Algorithm for Betweenness Centrality on the graph
*/
vector<double> BetweennessCentrality(Graph g);