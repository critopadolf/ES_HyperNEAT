#pragma once
// C++ Implementation of Quad Tree
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Used to hold details of a point
struct Point
{
    float x;
    float y;
    Point(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};

// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node()
    {
        data = 0;
    }
};

// The main quadtree class
class Quad
{
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;
    // Contains details of node
    Node* n;


    // Children of this tree
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
    }
    Quad(Point topL, Point botR)
    {
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
    }
    void insert(Node*);
    Node* search(Point);
    Node* searchRadius(std::vector<int>* nodesInRadius, Point p, float r);
    bool inBoundary(Point);
    bool inCircle(Point p, float r);

};

float pDist(Point p0, Point p1);
std::vector<Node> fillTree(Quad* qt, std::vector<std::vector<float>> points);


std::ostream& operator<<(std::ostream& os, const Node& v);