#include <vector>
#include <string>
#include <map>

// YOU CAN USE ONLY THE VECTORS, STRINGS AND MAPS FOR THIS ASSIGNMENT!

class GraphTemplate {
private:
    std::vector<NodeTemplate> nodes;
    MinHeapTemplate *minPriorityQueue;
    bool isDirected;

public:
    GraphTemplate(/* args */);
    ~GraphTemplate();

    // TODO: implement additional constructors
    // TODO: implement method for adding a node
    // TODO: implement method for removing a node
    // TODO: implement Prim
    // TODO: implement Bellman-Ford
    // TODO: implement printGraph function that generates a file written using the dot format
};

class NodeTemplate {
private:
    /* data */
    std::string label;
    std::map<NodeTemplate, int> adjacentNodes; // the int is for the weight od the egde
    NodeTemplate *parent;
    int distance; // aka key

public:
    NodeTemplate(/* args */);
    ~NodeTemplate();
    
    // TODO: implement additional constructors
    // TODO: implement method for adding a connection
    // TODO: implement method for removing a connection
    // TODO: implement methods for manipulating the parent and distance
};

class MinHeapTemplate {
private:
    MinHeapNodeTemplate *root;

public:
    MinHeapTemplate(/* args */);
    ~MinHeapTemplate();
    // TODO: implement method for restructuring the min-priority Queue
    // TODO: implement method for extracting the smaller element from the min-priority Queue
}

class MinHeapNodeTemplate{
private:
    /* data */
    NodeTemplate *node;
    MinHeapNodeTemplate *parent;
    MinHeapNodeTemplate *left;
    MinHeapNodeTemplate *right;

public:
    MinHeapNodeTemplate(/* args */);
    ~MinHeapNodeTemplate();

    // TODO: implement additional constructors
}
