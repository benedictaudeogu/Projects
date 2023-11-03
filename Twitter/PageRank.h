#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdexcept>
#include <unordered_map>

#include "Node.h"

using namespace std;

/*
 * PageRank.cpp PageRank.h
 * This class contains the functionality to create, manipulate, and organize data from Twitter users
 * regarding the following and return information ranking the nodes
 * 
 * This class relies on Node.cpp Node.h to create instances of nodes to hold specific information
 * about each user
 * 
 * This class contains information of the graph of interconnections on the twitter log files
 * 
 * eg. PageRank page;
 * The above is the correct use of creating an instance of this class. Any and all functionality
 * is self contained meaning, this class does not rely on other outside methods to PageRank.
 * Only Node.cpp Node.h is used to aquire information
 * 
 * The correct use of this class is to be used in main.cpp
 */

class PageRank{
private:
  //Contains the keys from the text file that contains the unique Node values
  unordered_map <int, Node> nodeMap_;
  
  //Contains the bfs organized nodes made by traversing nodes_keys
  vector<int> bfsNodes_;
  
  //Contains the key and pointer to the RootNode
  int rootKey_;
  Node* rootPointer_;
  
public:
  /*
   * createMap
   * Using the first edge file of the twitter data set. Node objects of every member of the .edges file 
   * are created and inserted in sets within an unordered map to demonstrate a directed relationship. A
   * pounsigneder of the nodeID itself is made and certain elements, such as the largest ID and the size of the 
   * file are stored as well.
   * 
   * Input: Manual integer key input from user of the file needed to be accessed in command prompt
   *        Reads values from Twitter log
   * Output: Graph of unique nodes and their interconnections
   * 
   * eg. 
   * In twitter file 6.edges:
   *    2 5
   * means that 6->2->5 and create map creates nodes to hold this information
   */
  void createMap();
  
  /*
   * makeEdge
   * Helper function to createMap that when passed infomration about the edge id's,
   * creates nodes and stores the information in the unordered _map of nodes.
   * 
   * Input: integers of origin and end of a directed edge
   * Output: Node objects stored in unordered_map
   */
  void makeEdge(int, int);
  
  /*
   * isPresent
   * Helper function for makeEdge, to check whether a node is present in a vector
   * to help create unique nodes and avoid repetion in creating the map
   * 
   * Input: vector of Nodes and integer key for id check
   * Output: Boolean value of whether the key exists already or not
   */
  bool isPresent(vector<Node>, int);
  
  /*
   * didVisit
   * Helper function for bfsMake to make sure that a Breath First Traversal of the graph
   * yields unique values to avoid repetion and infinite recursive loops of nodes that
   * share an edge.
   * 
   * 
   * Input: Vector of nodes visited, and integer key of current node
   * Output: Boolean value of whether the node has been visited or not
   */
  bool didVisit(vector<int> visited, int nodeId);
  
  /*
   * bfsMake
   * A graph traversla function that does Breath First Traversal of nodes and creates
   * a tree stored in vector bfsNodes_.
   * 
   * The purpose of this function is to organize the graph information to perform PageRank
   * as the graph has nodes that connect to each other. By performing bfsMake, the class
   * creates unique nodes values stored to trverse and target specific nodes.
   * 
   * Without this function, some nodes would be duplicated and result in infite recursion,
   * or multiple inaccurate PageRank calculations.
   * 
   * eg. If 2 follows 3 and 3 follows 2, this function prevents counting multiple
   * interactions between the two nodes.
   */
  void bfsMake();
  
  /*
   * PageRankMake
   * A graph traversal function that uses the information from bfsMake
   * to parse the tree of Nodes and account for times a node is targeted by another
   * 
   * If a node targets or follows another node, the targeted node will increase
   * its ranked_ value which in turn shows relevance of a node in relation with another
   * 
   * Main function for PageRank functionality
   */
  void PageRankMake();
  
  /*
   * PrintGraph
   * Helper function that organizes the bfsNodes_ tree to from highest ranked_ value to least
   * Then the function prints the values in finalPageRank.txt
   */
  void PrintGraph();
  
};