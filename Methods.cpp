#include "Graph.h"
#include "Node.h"
#include "Methods.h"
#include <set>
#include <queue>
#include <list>
#include <stack>
#include <cmath>

using std::set;
using std::queue;
using std::stack;
using std::min_element;
using std::list;

using namespace std;

vector<std::string> BFSTraversal(Graph g) {
    int size = g.getNodes().size();
    vector<bool> visited(size, false);
    vector<std::string> reviewers;

    //Call BFS Helper and go through all components
    for (int i = 0; i < size; i++) {
        if (!(visited[i])) {
            BFSHelper(i, g, visited, reviewers);
        }
    }

    return reviewers;
}

void BFSHelper(int index, Graph graph, vector<bool>& visited, vector<std::string>& reviewers) {
    queue<int> q;
 
    visited[index] = true;
    q.push(index);
 
    while(!q.empty())
    {
        index = q.front();
        reviewers.push_back(graph.getNodes()[index].getReviewerId());
        q.pop();
        vector<vector<int>> adjList = graph.getAdjLists();

        for (auto i = adjList[index].begin(); i != adjList[index].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
}

std::pair<vector<double>, vector<int>> Dijkstra(Graph g, int start) {
    int num_nodes = g.getNodes().size();
    vector<double> dist;
    vector<int> prev;

    set<int> s;
    //Use priority queue based on min_heap to store node indices
    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 0; i < num_nodes; i++) {
        dist.push_back(999999999999);
        prev.push_back(-1);
    }

    dist[start] = 0;

    for (int i = 0; i < num_nodes; i++) {
        q.push(i);
    }

    while (!(q.empty())) {
        int i = q.top();
        q.pop();
        s.insert(i);

        int count = 0;

        for (size_t j = 0; j < g.getAdjLists()[i].size(); j++) {
            Node n1 = g.getNodes()[i];
            
            //Change the distance to account for the added node and change previous as well
            Node n2 = g.getNodes()[g.getAdjLists()[i][j]];
            if (((dist[i] + g.calculateEdgeWeight(n1, n2)) <= dist[g.getAdjLists()[i][j]])) {
                dist[g.getAdjLists()[i][j]] = (dist[i] + g.calculateEdgeWeight(n1, n2));
                prev[g.getAdjLists()[i][j]] = i;
            }
        }
    }

    std::pair<vector<double>, vector<int>> output(dist, prev);

    return output;
}

vector<double> BetweennessCentrality(Graph g) {
    queue<int> q;
    stack<int> s;
    int num_nodes = g.getNodes().size();
    vector<double> dist;
    vector<vector<int>> pred;
    vector<int> shortest_paths;
    vector<double> dependency;
    vector<double> betweenness;

    for (int a = 0; a < num_nodes; a++) {
        betweenness.push_back(0.0);
    }

    //Parse through all nodes
    for (int i = 0; i < num_nodes; i++) {
        pred.clear();
        dist.clear();
        shortest_paths.clear();
        
        for (int j = 0; j < num_nodes; j++) {
            pred.push_back(vector<int>());
            
            dist.push_back(999999999999);
            shortest_paths.push_back(0);
        }

        dist[i] = 0.0;
        shortest_paths[i] = 1;
        q.push(i);

        //Store the nodes in a queue and stack to check when to stop

        while (!(q.empty())) {
            int x = q.front();
            q.pop();
            s.push(x);
            for (size_t k = 0; k < g.getAdjLists()[x].size(); k++) {
                int y = g.getAdjLists()[x][k];
                Node n1 = g.getNodes()[x];
                Node n2 = g.getNodes()[y];

                if (dist[y] == 999999999999) {
                    dist[y] = dist[x] + g.calculateEdgeWeight(n1, n2);
                    q.push(y);
                }

                if (std::abs(dist[y] - dist[x] + g.calculateEdgeWeight(n1, n2)) > 0.00000000001) {
                    shortest_paths[y] = shortest_paths[y] + shortest_paths[x];
                    pred[y].push_back(x);
                }
            }
        }

        dependency.clear();
        for (int d = 0; d < num_nodes; d++) {
            dependency.push_back(0.0);
        }

        while (!(s.empty())) {
            int top = s.top();
            s.pop();
            for (int m : pred[top]) {
                if (shortest_paths[top] != 0) {
                    dependency[top] = dependency[m] + (1.0 * shortest_paths[m] / shortest_paths[top]) * (1 + dependency[top]);
                } 
            }

            if (top != i) {
                betweenness[top] = betweenness[top] + dependency[top];
            }
        }
    }

    for (size_t b = 0; b < betweenness.size(); b++) {
        betweenness[b] = betweenness[b] / 2;
    }


    return betweenness;
}