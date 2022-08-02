Arjun Prabhu, Anuraag Mohanty, Edmon Guan, Ishaan Ramesh

12/13/2021

## CS 225 Final Project Results

### Dataset Size: 100 Reviews
### Dataset Category: Amazon Fashion

### Output Image:
![image info](results.png)

### BFS Output Description
We print out the reviewer IDs in the order our nodes are traversed using the BFS algorithm. Our test cases ensure that the nodes are traversed in the correct order and that all nodes are traversed even in graphs where certain nodes aren't connected in any way.

### Dijkstra's Output Description
We first print out the name of the source user that we use as a starting point for Dijkstra's when finding shortest paths. Then, after displaying the products reviewed by our source reviewer, we display the name of the reviewer obtained using our shortest path methodology, which finds the shortest path to a reviewer with more uncommon products than products that they've both reviewed. Finally, we print out product recommendations based on the products reviewed by the reviewer we identified using our shortest path algorithm. If no such reviewer is found using the shortest path algorithm, we just print out the products reviewed by the closest neighbor of our source node.

In the image above, the products reviewed by the source viewer were two different pairs of glasses, and the recommendations outputted by our algorithm were differently sized pants. We noticed that one of the Product ID's was repeated, which is due to duplicate reviews in the original dataset that we downloaded. Nonetheless, the output provided data meeting our expectations for the algorithm.

We ensure that this output is correct through our test cases, which more thoroughly cover whether the algorithm outputs the correct shortest path and distance values.

### Betweenness Centrality Output Description
In the preceding image, we outputted the top 10 most influential reviewers based on their corresponding betweenness ratings, which we acquired by sorting pairs of reviewers and their associated ratings. Our results indicated that the user with the name "Fhteacher" was the most influential according to our calculated betweenness ratings for each reviewer based on the given review data. 

We made a simplified version of our Betweenness Centrality ranking system in our test cases to make sure that it correctly identifies the most influential and least influential nodes.

