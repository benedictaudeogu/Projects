#include <iostream>

#include "PageRank.h"
#include "Node.h"

using namespace std;
/*
 * main.cpp
 * main implementation of the function and the method to create the project to rank graphs
 */

int main(){
  
  //create object rank and createMap and then PageRank the map
  PageRank rank;
  rank.createMap();
  rank.PageRankMake();
  
  return 0;
}