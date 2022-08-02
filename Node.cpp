#include "Node.h"

Node::Node(string reviewer, vector<string> products) {
    reviewerID = reviewer;
    productIDs = products;
}

string Node::getReviewerId() {
    return reviewerID;
}

vector<string> Node::getProductIDs() {
    return productIDs;
}

void Node::setReviewerId(string reviewer) {
    reviewerID = reviewer;
}

void Node::setProductIDs(vector<string> products) {
    productIDs = products;
}