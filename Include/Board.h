#pragma once
#include <iostream>
#include "Node.h"
#include <unordered_map>

class Board {

    private:

        int _numX;
        int _numY;
        float _nodeWidth;
        float _nodeHeight;
        int _numVertexAttributes;

        float _probabilityToFlip;

        std::unique_ptr<Node[]> _nodes;
        std::set<std::vector<int>> _edgePositions;
        std::vector<float> _vertices;
        std::vector<unsigned int> _indices;

        std::unordered_map<int, std::vector<float>> _typesToColor;

        void UpdateColor(int ID, int type);
        void UpdateType(int ID, int type);
        void PlaceSeeds(int numSeeds);

    public:

        Board(int numX, int numY);
        void Init();
        int GetID(int x, int y);
        void AddNeighbors(Node* node, int x, int y);
        void AddVertex(int x, int y);
        void AddIndex(int x, int y);
        void AddQuad(int ID, int x, int y);
        float* GetVertices();
        unsigned int GetVertexCount();
        unsigned int* GetIndices();
        unsigned int GetIndexCount();
        void PrintNodeAttributes();
        void PrintVertices();
        void PrintIndices();

        void SimulateTurn();


};