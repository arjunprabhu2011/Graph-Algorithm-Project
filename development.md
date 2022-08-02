# Development Log
Arjun Prabhu, Anuraag Mohanty, Edmon Guan, Ishaan Ramesh

We are starting the development log from the week after Thanksgiving break since our proposal rewrite was accepted during break, but we were unavailable to work on the project during that week. Therefore, Week 1 corresponds to the week directly following Thanksgiving break.
### Week 1 (11/29/21 - 12/05/21)
During Week 1, we first downloaded the json file corresponding to our dataset from the Stanford Dataset Collection. We then used the nlohmann json library for C++ to parse our data, which we stored as a Hash Map between reviewer IDs (functioning as keys) and the list of product IDs reviewed by each reviewer. We then used this map to construct our list of vertices in our Graph class by storing them in a custom Node class containing the needed information for each reviewer. In our Graph class, we also generated the edges for the graph as the nodes were being added sequentially, since we defined an edge as existent if two reviewers reviewed at least one product in common. After graph construction, we implemented the BFS algorithm and briefly started on Dijkstra's algorithm by defining our edge weights in our Graph class.
### Week 2 (12/06/21 - 12/13/21)
During Week 2, we implemented all of our main algroithms. With our graph constructed, we completed Dijkstra's Algorithm and the Betweenness Centrality Algorithm based on Brandes's implementation. We stored these in a separate file called Methods.cpp. We also wrote several test cases to test BFS, Dijkstra's Algorithm and Between Centrality. We edited main to have a better looking front end for the user to see when they run the program. We also finished all the final deliverables for the project. 


