#pragma once
#include "json.hpp"
#include <unordered_map>
#include <vector>

using json = nlohmann::json;
using std::unordered_map;
using std::vector;

/**
 *  Accepts json data and categorizes review data by reviewer ID, for usability in Graph structure
 * */
class ReviewParser {
    public:
        ReviewParser() = default;

        /**
         * Updates map between reviewers and reviewed products using json data for review to be added
         * */
        void addReview(json review_data);


        unordered_map< std::string, vector< std::string > >& getReviewerMap();
        unordered_map< std::string, std::string >& getNameMap();
        
    private:
        /* Maps reviewer ID (stored as string) to the 
           products they have reviewed (stored as a vector of strings containing product ID's) */
        unordered_map< std::string, vector< std::string > > reviewer_map_;
        unordered_map< std::string, std::string > name_map_;
};