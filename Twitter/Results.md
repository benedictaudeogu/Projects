PageRank in general essentially determines the importance of a web page based upon the number of web pages that are linked to it as well as the importance of those linked web pages. In terms of our project, the webpages would be the users, and their importance would be determined by how many followers they had. In our attempt to translate this relationship to our dataset, we for a final deliverable, will be printing our graph as a list of the nodes, from highest to lowest, based on their number of followers per node.

We had a time frame of almost five weeks to process our dataset and implement a PageRank algorithm that would print a list of the users from those who had the most followers, to those who had the least, for any valid file inputted. Our data set came from the Stanford Large Network Dataset Collection. We specifically dealt with the twitter files under the social networks category. 

Within the twitter directory, we only considered the nodeID.edges files as these represented the connection between the user(nodeID) and their followings inside the file. The files were extensive and plentiful, and so being conscious of our runtime limitations, we thought it would be best to limit the amount of data we processed. We decided to only look at one file and consider only those edges only instead. We found this to still be in agreement with our proposal because the nodeID.edges files for twitter demonstated a directed relationship in which the nodeID followed user1, in the first column, and user1 followed user2 in the second column of the file. This relationship was also in agreement with the terms needed to produce a PageRank of these users. 

Realizing that our code had to be tested for generalness, we got rid of the hardcoding we'd implemented, and made the pagerank listing appear for any valid files. In order to manipulate and test which of these files to organize, we implemented a required statment from the user through the command prompt for an integer value of the file name. This way we can manage the memory used and the specifc files of twitter data targeted. 

To process the data, we created a node object of every member inside the chosen file. The nodes were then stored by ID name in an unordered map. In order to maintain the following hierarchy and demonstrate the directed relationship between who followed who, a set was assigned to each node. Inside that set would be everybody the node followed. This way, we would only have to traverse the map by ID and for each ID, we would be able to create vertices, if they existed.

As a two person team, our requirements consisted of implementing one uncovered algorithm (PageRank) and one ceovered algorithm (Breadth First Search).

Node.cpp Node.h

Contains the functions to retrieve and set private variables in the class such as setting the id_ and ranked_ variables. Also contains constructors to initialize these values. Furthermore, the functions contain an overloaded operator function that returns true which is used in comparing the class node to other objects of the type.

PangeRank.cpp PageRank.h

Contains the functions to organize and create objects Node to perform page rank.

PageRank::createMap() -> inputs integer from user to retireve fils and create nodes and organize them in a map to revove duplicates

PageRank::makeEdge(int, int) -> inputs integer values of node keys to create object Nodes and store in map

PageRank::isPresent(vector<Node>, int) -> compares input of vector and a key to see if a key has already been entered and returns bool value

PageRank::didVisit(vector<int>, int) -> compares the input key to see if a key is duplicated to have been visited or not, returns bool value

PageRank::bfsMake() -> uses the graph already created with createMap and organizes the nodes to create a bfs tree to iterate through

PageRank::PageRankMake() -> uses the bfs tree to rank the pages based on the value 

PageRank::PrintGraph() -> uses the page ranked tree to then print to text file finalPageRank.txt the ordered list of most followers to least in page rank form
  
OUTPUT: The output of the functions and files once performed and executed is found in finalPageRank.txt. The current finalPageRank.txt found on github is the ranked pages result of 12831.edges. Since the file contains over 300 lines, it is not beneficial to have included this file in this result.md file. However looking at the results of running the code on the 12831.edges file shows that the least followed individual is the root node 12831 as it is a root node and thus does not have any node following them.

Confirmation of these tests can be found with looking at the 12831.edges file and using ctrl + f to search for occuring values to see how often these results occure and how the finalPageRank.txt show these results.

DISCOVERIES: Through the testing and implementation of this project there were some discoveries made on how each node interactes with another. We learned that the root node follows other nodes, but is not followed meaning in twitter data there exists nodes without any follows. This overall shows in twitter data that there are isolated cluster of nodes with their own group of traits that do not interact with other clusters. This shows the social heiarchy within each cluster and how similar to social interaction where a group of friends form cliques, twitter groups alos form similar groups that are isolated.

This overall answers the leading question of finding a way to organize and learn about twitter data followers through finding who they follow and how that ranks them socially amount their friends.
