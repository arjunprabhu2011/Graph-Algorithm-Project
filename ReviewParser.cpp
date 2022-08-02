#include "ReviewParser.h"

void ReviewParser::addReview(json review_data) {
    reviewer_map_[review_data["reviewerID"]].push_back(review_data["asin"]);
    name_map_[review_data["reviewerID"]] = review_data["reviewerName"];
}

unordered_map< std::string, vector< std::string > >& ReviewParser::getReviewerMap() {
    return reviewer_map_;
}

unordered_map< std::string, std::string >& ReviewParser::getNameMap() {
    return name_map_;
}
