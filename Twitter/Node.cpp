#include "Node.h"

using namespace std;

//Initialize object of a Node with ranked
Node::Node(){
  ranked_ = 0;
}

//Initialize object of a Node with id and ranked
Node::Node(int id){
  id_ = id;
  ranked_ = 0;
}

//return value of id
int Node::get_id(){
  return id_;
}

//return value of Ranked
int Node::get_ranked(){
  return ranked_;
}


//add 1 to Ranked
void Node::add_ranked(){
  ranked_ = ranked_ + 1;
}

//return true when compared with the address of a node value for comparasion and organization
bool Node::operator< (const Node & n) const{
  return true;
}

