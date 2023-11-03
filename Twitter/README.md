PAGE RANK

Overview:

This code base performs the functionality of answering the question: How do we organize Twitter User data to learn about how
each user interacts with another? By using this code base, one will be able to organize the data found in Twitter directory in
the same fashion as Page Rank in webpages.

FILES:

Twitter (Directory): Contains [nodeID].edges files that each contain the relationship between the root node [nodeID] and subsequent
nodes that [nodeID] follows. the [nodeID].edges files are organized in the following manner...

1 2

14  10

1 6

where [nodeID] follows 1 and 14 as they are the leftmost nodes, while 1 follows 2 and 6 and 14 follows 10 giving the following tree

nodeID -> 1 -> 2

nodeID -> 1 -> 6

nodeID -> 14 -> 10
      
*note that the files contain duplicates however, since the first root node [nodeID] always follows the first column, there are no isolated nodes in the created
graphs.


Makefile: Contains the method to compile the code into one executable by the name of final. to run the make file use make command


Node.cpp Node.h: This class contains the essense for each node on the graph created by the PageRank Class. The correct use of this class is to provide information pertaining to the position, state and characteristic of a node in the graph of Twitter user connection. 

Eg. Node node(5);

The above is the correct way to initialize an object of this class outside and it will create a object with id value 5 and ranked value 0.


PageRank.cpp PageRank.h: This class contains the functionality to create, manipulate, and organize data from Twitter users regarding the following and return information ranking the nodes. This class relies on Node.cpp Node.h to create instances of nodes to hold specific information about each user. This class contains information of the graph of interconnections on the twitter log files

eg. PageRank page;

The above is the correct use of creating an instance of this class. Any and all functionality is self contained meaning, this class does not rely on other outside methods to PageRank. Only Node.cpp Node.h is used to aquire information. The correct use of this class is to be used in main.cpp


main.cpp: This file contains the essense of the entire project as it uses the other classes to execute the function of each class to create and organize data.


finalPageRank.txt: contains the outputed print of the organized page ranked twitter user data


HOW TO MAKE THE CODEBASE:

1) Pull the github repository

2) Open command prompt and change directory to the correct pulled code base

3) run 'make' command

4) run './final' command

5) user input the correct file that you want to organize. 

*Note only integer values are excepted, any other values will throw errors. Make sure that the correct file name is also used (i.e. 12831 for 12831.edges) otherwise
errors will be thrown or only one node will be made.

6) The results will be in finalPageRank.txt with the correct ordering of the node values


TESTS:

Throughout the project, we have used the tests already created in the form of the Twitter directory and .edges files. We have parsed
the output with the input of the .edges files to see if the general output of the page rank matches the input of the files. Note the output
will have the root nodeID for the nodeID.edges file as the last printed node as there are few instances for internal nodes pointing to the
root node.
