#include "quadtree.h"
// Insert a node into the quadtree
void Quad::insert(Node* node)
{
    
    if (node == NULL) {
        return;
    }

    // Current quad cannot contain it
    if (!inBoundary(node->pos)) {
        return;
    }

    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 0.001 &&
        abs(topLeft.y - botRight.y) <= 0.001)
    {
        if (n == NULL) {
            std::cout << (*node) << "\n";
            n = node;
        }
        return;
    }

    if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(node);
        }

        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                        (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                        botRight.y));
            botLeftTree->insert(node);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        topLeft.y),
                    Point(botRight.x,
                        (topLeft.y + botRight.y) / 2));
            topRightTree->insert(node);
        }

        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                        (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(node);
        }
    }
}

// Find a node in a quadtree
Node* Quad::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
        return NULL;

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != NULL)
    {
        return n;
    }

    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }

        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }

        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};

Node* Quad::searchRadius(std::vector<int>* nodesInRadius, Point p, float r)
{
    if (!inCircle(p, r))
        return NULL;
    if (n != NULL && pDist(n->pos, p) <= r)
    {
        nodesInRadius->push_back(n->data);
    }
    if(n == NULL)
        std::cout << "node null\n";
    if (topLeftTree == NULL && botLeftTree == NULL && topRightTree == NULL && botRightTree == NULL)
        std::cout << "all null\n";
    if (topLeftTree != NULL)
        topLeftTree->searchRadius(nodesInRadius, p, r);
    if (botLeftTree != NULL)
        botLeftTree->searchRadius(nodesInRadius, p, r);
    if (topRightTree != NULL)
        topRightTree->searchRadius(nodesInRadius, p, r);
    if (botRightTree != NULL)
        botRightTree->searchRadius(nodesInRadius, p, r);

};


// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
    /*
    std::cout << p.x << " >= " << topLeft.x << "\t" << (p.x >= topLeft.x) << "\n";
    std::cout << p.x << " <= " << botRight.x << "\t" << (p.x <= botRight.x) << "\n";
    std::cout << p.y << " >= " << topLeft.y << "\t" << (p.y >= topLeft.y) << "\n";
    std::cout << p.y << " <= " << botRight.y << "\t" << (p.y <= botRight.y) << "\n";
    */
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y >= topLeft.y &&
        p.y <= botRight.y);
}
// Check if current quadtree is within a circle
bool Quad::inCircle(Point p, float r)
{
    //https://stackoverflow.com/questions/21089959/detecting-collision-of-rectangle-with-circle
    float rectWidth = abs(botRight.x - topLeft.x);
    float rectHeight = abs(botRight.y - topLeft.y);
    float distX = abs(p.x - (topLeft.x - rectWidth) / 2);
    float distY = abs(p.y - (topLeft.y - rectHeight) / 2);
    if (distX > (rectWidth / 2) + r) { return false; }
    if (distY > (rectHeight / 2) + r) { return false; }
    if (distX <= (rectWidth / 2)) { return true; }
    if (distY <= (rectHeight / 2)) { return true; }

    float dx = distX - rectWidth / 2;
    float dy = distY - rectHeight / 2;
    return (dx * dx + dy * dy <= (r * r));
}

float pDist(Point p0, Point p1)
{
    float dix = p1.x - p0.x;
    float diy = p1.y - p0.y;
    return sqrtf(dix * dix + diy * diy);
}

std::vector<Node> fillTree(Quad* qt, std::vector<std::vector<float>> points)
{
    std::vector<Node> nodes(points.size());
    for (int x = 0; x < points.size(); x++)
    {
        nodes[x] = Node(Point(points[x][0], points[x][1]), x);
        qt->insert(&nodes[x]);
        //std::cout << *(qt->n);
    }
    
    return nodes;
}

std::ostream& operator<<(std::ostream& os, const Node& v)
{
    os << "[ x: " << v.pos.x << ", y: " << v.pos.y << ", data: " << v.data << " ]\n";
    return os;
}