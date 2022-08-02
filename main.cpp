#include <iostream>
#include <fstream>
#include "json.hpp"
#include "ReviewParser.h"
#include "Node.h"
#include "Graph.h"
#include "Methods.h"

using json = nlohmann::json;
using std::ifstream;
using std::string;

int main()
{
    json review_info;

    // Currently running on smaller dataset locally to test functionality
    ifstream review_input("AMAZON_FASHION_5.json");

    ReviewParser parser;

    // Parse through individual reviews to update map of reviewer ids to ids of products reviewed
    while (review_input.good()) {
        review_input >> review_info;
        parser.addReview(review_info);
        review_input.get();
    }

    Graph g(parser.getReviewerMap().size());

    // Print out the list of product ids corresponding to reviews by each reviewer
    for (auto it = parser.getReviewerMap().begin(); it != parser.getReviewerMap().end(); ++it) {
        Node n(it->first, it->second);
        g.addNode(n);
    }

    unordered_map< std::string, std::string > reviewerToNameMap = parser.getNameMap();

    size_t sourceIndex = 1;

    vector<std::string> BFSIds = BFSTraversal(g);
    std::cout << "Reviewer IDs Traversed by BFS" << std::endl;
    for (string ID: BFSIds) {
        std::cout << ID << std::endl;
    }

    std::cout << std::endl;

    std::pair<vector<double>, vector<int>> dijkstra_output = Dijkstra(g, sourceIndex);
    vector<double> dist = dijkstra_output.first;
    vector<int> prev = dijkstra_output.second;

    double mindist = 999999999999;
    int minIndex = -1;

    std::cout << "Product Recommendations From Dijkstra's" << std::endl;

    for (size_t i = 0; i < dist.size(); i++) {
        Node n1 = g.getNodes()[sourceIndex];
        Node n2 = g.getNodes()[i];

        vector<string> vec1(n1.getProductIDs());
        vector<string> vec2(n2.getProductIDs());
        vector<string> intersections(std::max(vec1.size(), vec2.size()));

        sort(vec1.begin(), vec1.end());
        sort(vec2.begin(), vec2.end());
        vector<string>::iterator end;
        end = set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), intersections.begin());
    
        size_t common_values = 0;
        vector<string>::iterator it = intersections.begin();
        while(it != end) {
            common_values++;
            it++;
        }

        size_t uncommon_values = vec1.size() + vec2.size() - 2 * common_values;
        if (dist[i] < mindist && dist[i] != 0 && uncommon_values > common_values) {
            mindist = dist[i];
            minIndex = i;
        }
    }

    if (minIndex == -1) {
        std::cout << "No recommendations found based on current reviewer data for reviewer: ";
        std::cout << reviewerToNameMap.at(g.getNodes()[sourceIndex].getReviewerId()) << std::endl;
        std::cout << "Products Reviewed by Source User: " << std::endl;
        for (string product: g.getNodes()[sourceIndex].getProductIDs()) {
            std::cout << "Product ID (asin): ";
            std::cout << product << std::endl;
        }

        std::cout << std::endl;

        for (size_t i = 0; i < dist.size(); i++) {
            if (dist[i] < mindist && dist[i] != 0) {
                mindist = dist[i];
                minIndex = i;
            }
        }
             
        std::cout << "Here are some product recommendations based on the closest reviewer to you" << std::endl;

        std::cout << "User Utilized for Recommendations: ";
        std::cout << reviewerToNameMap.at(g.getNodes()[minIndex].getReviewerId()) << std::endl;
        std::cout << std::endl;
        std::cout << "Product Recommendations Based on Algorithm: " << std::endl;
        for (string product: g.getNodes()[minIndex].getProductIDs()) {
            std::cout << "Product ID (asin): ";
            std::cout << product << std::endl;
        }

    } else {
        std::cout << "Source User: ";
        std::cout << reviewerToNameMap.at(g.getNodes()[sourceIndex].getReviewerId()) << std::endl;
        std::cout << "Products Reviewed by Source User: " << std::endl;
        for (string product: g.getNodes()[sourceIndex].getProductIDs()) {
            std::cout << "Product ID (asin): ";
            std::cout << product << std::endl;
        }

        std::cout << std::endl;

        std::cout << "User Utilized for Recommendations: ";
        std::cout << reviewerToNameMap.at(g.getNodes()[minIndex].getReviewerId()) << std::endl;
        std::cout << std::endl;
        std::cout << "Product Recommendations Based on Algorithm: " << std::endl;
        for (string product: g.getNodes()[minIndex].getProductIDs()) {
            std::cout << "Product ID (asin): ";
            std::cout << product << std::endl;
        }

        std::cout << std::endl;
    }

    vector<double> betweenness_ratings = BetweennessCentrality(g);
    vector<std::pair<double, std::string>> betweennessByID;
    for (size_t i = 0; i < betweenness_ratings.size(); i++) {
        betweennessByID.push_back(std::pair<double, std::string>(betweenness_ratings[i], g.getNodes()[i].getReviewerId()));
    }

    std::cout << std::endl;

    std::sort(betweennessByID.begin(), betweennessByID.end());

    size_t rank = 1;
    std::cout << "Top Reviewers From Betweenness Ratings" << std::endl;
    for (size_t i = betweenness_ratings.size() - 1; i > betweenness_ratings.size() - 11; i--) {
        std::cout << rank;
        std::cout << ". ";
        std::cout << reviewerToNameMap.at(betweennessByID[i].second);
        std::cout << ": ";
        std::cout << betweennessByID[i].first << std::endl;
        rank++;
    }

    return 0;
}