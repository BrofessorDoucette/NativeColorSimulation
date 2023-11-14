# pragma once
#include <set>
#include <iostream>
#include <vector>

class Node {
        

    public:
        int ID;
        int LocX;
        int LocY;
        int Type;

        std::set<std::vector<int>> Neighbors;


        Node();
        void AddNeighbor(std::vector<int> neighbor);
};