#include "Node.h"
#include <iostream>
#include <vector>


Node::Node(){

    Neighbors = std::set<std::vector<int> >();

    
}

void Node::AddNeighbor(std::vector<int> neighbor){

    Neighbors.insert(neighbor);

}