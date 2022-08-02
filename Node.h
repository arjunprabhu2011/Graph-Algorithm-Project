#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

/**
* Class for a node in the graph. Contains reviewer id and a vector of product IDs. 
*/
class Node {
    private:
        string reviewerID;
        vector<string> productIDs;

    public:
        Node(string reviewer, vector<string> products);
        string getReviewerId();
        vector<string> getProductIDs();
        void setReviewerId(string reviewer);
        void setProductIDs(vector<string> products);
};