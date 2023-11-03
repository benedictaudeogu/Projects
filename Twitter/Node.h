#pragma once

#include <iostream>
#include <vector>

using namespace std;

/*
 * Node.cpp Node.h
 * This class contains the essense for each node on the graph created by the PageRank Class.
 * 
 * The correct use of this class is to provide information pertaining to the position, state
 * and characteristic of a node in the graph of Twitter user connection.
 * 
 * Eg. Node node(5);
 * The above is the correct way to initialize an object of this class outside and it will
 * create a object with id value 5 and ranked value 0.
 */

class Node{
private:
  //Private variables pertaining to this class that store information about
  //the characteristic of a node such as its id_ and ranked_.
  
  //id_ stores the name of the node key, and ranked stores the number of nodes that
  //point to node id
  int id_;
  int ranked_;
  
public:
  //Public variables that hold the functionality of this class such as initialization
  //and manipulation.
  
  //Constructors initialization for the class
  Node(int);
  Node();
  
  //functions to retrieve information outside of the class
  int get_id();
  int get_ranked();
  
  //function to manipulate data within the class
  void add_ranked();
  
  //Public variable vector that stores the relationship of this object with other objects of the same class
  //neighbors_ stores the Nodes that an object of this class follows on Twitter
  vector<Node> neighbors_;
  
  //Operator for the purpose of comparing the node in relation with other nodes
  bool operator< (const Node & n) const;

};