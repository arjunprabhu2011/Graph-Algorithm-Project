#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "algorithm_tests.h"
#include "../Node.h"
#include "../Graph.h"
#include "../ReviewParser.h"
#include "../Methods.h"

using std::string;
using std::vector;

TEST_CASE("BFS Traverses All Nodes In Order") {
    Graph g(6);
    Node n1("hello", {"a", "b", "c", "d"});
    Node n2("arjun", {"e", "f", "g", "h"});
    Node n3("anuraag", {"a", "b", "c", "k", "f"});
    Node n4("andy", {"njdsn", "njdiosn"});
    Node n5("edmon", {"n"});
    Node n6("ishaan", {"p", "q", "njdsn"});
    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);
    g.addNode(n5);
    g.addNode(n6);

    vector<string> reviewers = BFSTraversal(g);
    vector<string> expected = {"hello", "anuraag", "arjun", "andy", "ishaan", "edmon"};

    // Make sure that BFS traverses entire graph
    REQUIRE(expected == reviewers);
}

TEST_CASE("BFS Traverses All Nodes in Graph With No Edges") {
    Graph g(3);
    Node n1("edmon", {"a"});
    Node n2("arjun", {"e"});
    Node n3("anuraag", {"b"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);

    vector<string> reviewers = BFSTraversal(g);
    vector<string> expected = {"edmon", "arjun", "anuraag"};

    REQUIRE(expected == reviewers);
}

TEST_CASE("BFS Traverses Nodes of Equal Distance Away in Correct Order") {
    Graph g(3);
    Node n1("edmon", {"a", "b", "c"});
    Node n2("arjun", {"a", "b"});
    Node n3("anuraag", {"b", "c"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);

    vector<string> reviewers = BFSTraversal(g);
    vector<string> expected = {"edmon", "arjun", "anuraag"};

    REQUIRE(expected == reviewers); 
}

TEST_CASE("Dijkstra's Returns Correct Distances and Path") {
    Graph g(4);
    Node n1("hello", {"a", "b", "c"});
    Node n2("edmon", {"a", "b", "e"});
    Node n3("arjun", {"a", "d", "f"});
    Node n4("anuraag", {"e", "f"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);

    std::pair<vector<double>, vector<int>> output = Dijkstra(g, 0);
    vector<double> dist_expected = {0.0, 0.5, 1.0, 1.5};
    vector<int> prev_expected = {-1, 0, 0, 1};

    REQUIRE(dist_expected == output.first);
    REQUIRE(prev_expected == output.second);
}

TEST_CASE("Dijkstra's Returns Correct Distances and Path for Disconnected Nodes") {
    Graph g(4);
    Node n1("hello", {"a"});
    Node n2("edmon", {"b"});
    Node n3("arjun", {"c"});
    Node n4("anuraag", {"d"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);

    std::pair<vector<double>, vector<int>> output = Dijkstra(g, 0);
    vector<double> dist_expected = {0.0, 999999999999, 999999999999, 999999999999};
    vector<int> prev_expected = {-1, -1, -1, -1};

    REQUIRE(dist_expected == output.first);
    REQUIRE(prev_expected == output.second);
}

TEST_CASE("Betweenness Centrality returns correct node with highest and lowest betweenness") {
    Graph g(4);
    Node n1("hello", {"a", "b", "e", "f"});
    Node n2("edmon", {"a", "b", "e"});
    Node n3("arjun", {"a", "d", "f"});
    Node n4("anuraag", {"d", "g"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);

    vector<double> output = BetweennessCentrality(g);

    vector<std::pair<double, std::string>> betweennessByID;
    for (size_t i = 0; i < output.size(); i++) {
        betweennessByID.push_back(std::pair<double, std::string>(output[i], g.getNodes()[i].getReviewerId()));
    }

    std::sort(betweennessByID.begin(), betweennessByID.end());
    
    //Checking the most and least influential nodes in the graph
    REQUIRE("anuraag" == betweennessByID[0].second);
    REQUIRE("hello" == betweennessByID[3].second);
}

TEST_CASE("Betweenness Centrality outputs default value of zero if there are no connections") {
    Graph g(4);
    Node n1("hello", {"a"});
    Node n2("edmon", {"b"});
    Node n3("arjun", {"c"});
    Node n4("anuraag", {"d"});

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);
    vector<double> output = BetweennessCentrality(g);
    for (size_t i = 0; i < output.size(); i++) {
        REQUIRE(0.0 == output[i]);
    }
}

