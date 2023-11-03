#include "PageRank.h"

using namespace std;


void PageRank::createMap(){
  //get integer input from user, if file does not exist, only 1 node is created 
  cout << "Please enter a root key to map: ";
  cin >> rootKey_;
  //TODO: add exception for the correct key, make sure it is correct
  
  string filename = "twitter/"+to_string(rootKey_)+".edges";
  if(!(filename.compare("twitter/"+to_string(rootKey_)+".edges"))){
    //create root node
    Node node(rootKey_);
    nodeMap_[rootKey_] = node;
    rootPointer_ = &node;
    
    //read from file to create edges
    ifstream file(filename);
    string line;
    while(getline(file,line)){
      istringstream ss(line);
      string first;
      getline(ss, first, ' ');
      string second;
      getline(ss, second, ' ');
      
      int temp1 = stoi(first);
      int temp2 = stoi(second);
      
      //pass information to create edges
      makeEdge(rootKey_, temp1);
      makeEdge(temp1, temp2);
    }
    file.close();
  }
}

void PageRank::makeEdge(int origin, int following){
  //if new value for following or origin, create a key in the map to that edge
  if(!(nodeMap_.find(following) != nodeMap_.end())){
    Node edge(following);
    nodeMap_[following] = edge;
  }
  //if the node is not present in neighbors_, add it 
  Node insertTo(following);
  if(!isPresent(nodeMap_[origin].neighbors_, following)){
    nodeMap_[origin].neighbors_.push_back(insertTo);
  }
  
}

bool PageRank::isPresent(vector<Node> neighbors, int following){
  //check if node is present,and return if it is my iterating through the keys
  for(int i = 0; i < neighbors.size(); i++){
    if(neighbors[i].get_id() == following){
      return true;
    }
  }
  return false;
}

bool PageRank::didVisit(vector<int> visited, int nodeId){
  //check if key has been targeted before,and return if it is my iterating through the keys
  for(int i = 0; i <visited.size(); i++){
    if(visited[i] == nodeId){
      return true;
    }
  }
  return false;
}

void PageRank::bfsMake(){
  //create list of queues to nodes that we need to go to and vector of nodes we been to
  list<int> node_queue;
  vector<int> visited;
  //push the root node to the queue and vector and mark as visited
  node_queue.push_back(rootPointer_->get_id());
  visited.push_back(rootPointer_->get_id());
  bfsNodes_.push_back(rootPointer_->get_id());
  
  //while the queue is not empty create a bfsTree from the graph
  while(!node_queue.empty()){
    int current_node = node_queue.front();
    node_queue.pop_front();
    
    //check if visited the node before
    for(int i = 0; i < nodeMap_[current_node].neighbors_.size(); i++){
      if(!didVisit(visited,nodeMap_[current_node].neighbors_[i].get_id())){
        node_queue.push_back(nodeMap_[current_node].neighbors_[i].get_id());
        visited.push_back(nodeMap_[current_node].neighbors_[i].get_id());
        bfsNodes_.push_back(nodeMap_[current_node].neighbors_[i].get_id());
      }
    }
  }
  
}


void PageRank::PageRankMake(){
  //make bfstree and iterate through the tree to add ranked_ values if a node is connected to another
  bfsMake();
  for(int i = 0; i < bfsNodes_.size(); i++){
    for(int j = 0; j < nodeMap_[bfsNodes_[i]].neighbors_.size(); j++){
      //add to the ranked value
      nodeMap_[bfsNodes_[i]].neighbors_[j].add_ranked();
    }
  }
  //print the graph
  PrintGraph();
}

void PageRank::PrintGraph(){
  //what we need to print
  vector<Node> toPrint;
  
  //Iterate through the bfsNodes_ tree created and if organize nodes based on largest ranked value
  for(int i = 0; i < bfsNodes_.size(); i++){
    if(toPrint.size() == 0){
      toPrint.push_back(nodeMap_[bfsNodes_[0]]);
      continue;
    }
    vector<Node>::iterator it;
    for(it = toPrint.begin(); it != toPrint.end(); ++it){
      if(nodeMap_[bfsNodes_[i]].get_ranked() >= it->get_ranked()){
        toPrint.insert(it, nodeMap_[bfsNodes_[i]]);
        break;
      }
      toPrint.push_back(nodeMap_[bfsNodes_[i]]);
      break;
    }
  }
  
  //create a file and print the results to file
  fstream file;
  file.open("finalPageRank.txt",ios::out);
  
  if(!file.is_open()){
    cout << "Error in opening file!" << endl;
    return;
  }
  if(file.is_open()){
    file << "PageRank from largest to least following: " << endl;
    for(int i =0; i < toPrint.size(); i++){
      file << toPrint[i].get_id() << endl;
    }
  }
  file.close();
}
