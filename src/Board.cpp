#include "Board.h"
#include "Node.h"
#include <iostream>
#include <unordered_map>
#include <cstdlib>


Board::Board(int numX, int numY){


    _numX = numX;
    _numY = numY;
    _nodeWidth = 2.0f / numX;
    _nodeHeight = 2.0f / numY;
    _numVertexAttributes = 6;
    _typesToColor = std::unordered_map<int, std::vector<float>>();
    _typesToColor[-1] = {1.0f, 1.0f, 1.0f};
    _typesToColor[0] = {1.0f, 0.0f, 0.0f};
    Init();
    PlaceSeeds(3);
}

void Board::Init(){

    _nodes = std::make_unique<Node[]>(_numX * _numY);

    for(int x = 0; x < _numX; x++){

        for(int y = 0; y < _numY; y++){
            
            int ID = x * _numY + y;

            Node* node = &_nodes[ID];
            node->LocX = x;
            node->LocY = y;
            node->ID = ID;
            node->Type = -1;
            
            AddNeighbors(node, x, y);
            AddQuad(ID, x, y);

        }
    }

}

int Board::GetID(int x, int y){

    return x * _numY + y;
}

void Board::AddNeighbors(Node* node, int x, int y){

    if(x == 0){

        if(y == 0){

            node->AddNeighbor({x + 1, y});
            node->AddNeighbor({x + 1, y+1});
            node->AddNeighbor({x, y+1});
        } else if (y == _numY - 1){

            node->AddNeighbor({x + 1, y});
            node->AddNeighbor({x + 1, y - 1});
            node->AddNeighbor({x, y - 1});

        } else {

            node->AddNeighbor({x, y + 1});
            node->AddNeighbor({x + 1, y + 1});
            node->AddNeighbor({x + 1, y});
            node->AddNeighbor({x + 1, y - 1});
            node->AddNeighbor({x, y - 1});
        }

    } else if(x == _numX - 1){

        if(y == 0){

            node->AddNeighbor({x - 1, y});
            node->AddNeighbor({x - 1, y + 1});
            node->AddNeighbor({x, y + 1});
        } else if (y == _numY - 1){

            node->AddNeighbor({x - 1, y});
            node->AddNeighbor({x - 1, y - 1});
            node->AddNeighbor({x, y - 1});
        } else {

            node->AddNeighbor({x, y - 1});
            node->AddNeighbor({x - 1, y - 1});
            node->AddNeighbor({x - 1, y});
            node->AddNeighbor({x - 1, y + 1});
            node->AddNeighbor({x, y + 1});
        }

    } else {

        if (y == 0){

            node->AddNeighbor({x - 1, y});
            node->AddNeighbor({x - 1, y + 1});
            node->AddNeighbor({x, y + 1});
            node->AddNeighbor({x + 1, y + 1});
            node->AddNeighbor({x + 1, y});
        } else if (y == _numY - 1){

            node->AddNeighbor({x - 1, y});
            node->AddNeighbor({x - 1, y - 1});
            node->AddNeighbor({x, y - 1});
            node->AddNeighbor({x + 1, y - 1});
            node->AddNeighbor({x + 1, y});
        } else {

            node->AddNeighbor({x - 1, y - 1});
            node->AddNeighbor({x, y - 1});
            node->AddNeighbor({x + 1, y - 1});
            node->AddNeighbor({x + 1, y});
            node->AddNeighbor({x + 1, y + 1});
            node->AddNeighbor({x, y + 1});
            node->AddNeighbor({x - 1, y + 1});
            node->AddNeighbor({x - 1, y});
        }
    }
}

void Board::AddVertex(int x, int y){

    _vertices.push_back(-1.0f + x * _nodeWidth);
    _vertices.push_back(-1.0f + y * _nodeHeight);
    _vertices.push_back(0.0f);

    _vertices.push_back(1.0f);
    _vertices.push_back(1.0f);
    _vertices.push_back(1.0f);
}

void Board::AddIndex(int ID, int offset){

    _indices.push_back(_numVertexAttributes * ID + offset);
}

void Board::AddQuad(int ID, int x, int y){

    AddVertex(x, y);
    AddIndex(ID, 0);
    AddVertex(x + 1, y);
    AddIndex(ID, 1);
    AddVertex(x + 1, y + 1);
    AddIndex(ID, 2);
    AddVertex(x, y);
    AddIndex(ID, 3);
    AddVertex(x + 1, y + 1);
    AddIndex(ID, 4);
    AddVertex(x, y + 1);
    AddIndex(ID, 5);
}

float* Board::GetVertices(){

    return &_vertices[0];
}

unsigned int Board::GetVertexCount(){

    return (unsigned int) _vertices.size();
}

unsigned int* Board::GetIndices(){

    return &_indices[0];
}

unsigned int Board::GetIndexCount(){
    
    return (unsigned int) _indices.size();
}

void Board::PrintNodeAttributes(){

    for(int x = 0; x < _numX; x++){

        for(int y = 0; y < _numY; y++){

            Node* node = &_nodes[GetID(x, y)];
            std::cout << "ID: " << node->ID << std::endl;
            std::cout << "locX: " << node->LocX << std::endl;
            std::cout << "locY: " << node->LocY << std::endl;
            std::cout << "seed: " << node->Type << std::endl;

            for(auto& neighbor : node->Neighbors){
                std::cout << "(" << neighbor[0] << "," << neighbor[1] << ")" << std::endl;
            }
        }
    }
}

void Board::PrintVertices(){

    for(auto& vertexAttribute : _vertices){

        std::cout << vertexAttribute << std::endl;
    }
}

void Board::PrintIndices(){

    for(auto& index : _indices){

        std::cout << index << std::endl;
    }
}

void Board::UpdateColor(int ID, int type){

    int startOfTile = 6 * _numVertexAttributes * ID; //Six vertices per tile

    for(int v = 0; v < 6; v++){

        _vertices[startOfTile + v * _numVertexAttributes + 3] = _typesToColor[type][0];
        _vertices[startOfTile + v * _numVertexAttributes + 4] = _typesToColor[type][1];
        _vertices[startOfTile + v * _numVertexAttributes + 5] = _typesToColor[type][2];
    }
}

void Board::PlaceSeeds(int numSeeds){

    for(int i = 0; i < numSeeds; i++){

        int x = rand() % _numX;
        int y = rand() % _numY;

        int ID = GetID(x, y);
        UpdateColor(ID, 0);

        std::cout << "Placed seed at: (" << x << ", " << y << ")" << std::endl;
        
    }

}