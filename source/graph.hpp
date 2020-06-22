#include <map>
#include <string>
#include <vector>

// YOU CAN USE ONLY THE VECTORS, STRINGS AND MAPS FOR THIS ASSIGNMENT!

class Node {
 private:
  /* data */
  std::string label;
  std::map<Node, int> adjacentNodes;  // the int is for the weight od the egde
  Node* parent;
  int distance;  // aka key

 public:
  Node(/* args */);
  ~Node();

  // TODO: implement additional constructors
  // TODO: implement method for adding a connection
  // TODO: implement method for removing a connection
  // TODO: implement methods for manipulating the parent and distance
};

class MinHeapNode {
 private:
  /* data */
  Node* node;
  MinHeapNode* parent;
  MinHeapNode* left;
  MinHeapNode* right;

 public:
  MinHeapNode(/* args */);
  ~MinHeapNode();

  // TODO: implement additional constructors
};

class MinHeap {
 private:
  MinHeapNode* root;

 public:
  MinHeap(/* args */);
  ~MinHeap();
  // TODO: implement method for restructuring the min-priority Queue
  // TODO: implement method for extracting the smaller element from the
  // min-priority Queue
};

class Graph {
 private:
  std::vector<Node> nodes;
  MinHeap* minPriorityQueue;
  bool isDirected;

 public:
  Graph(/* args */);
  ~Graph();

  // TODO: implement additional constructors
  // TODO: implement method for adding a node
  // TODO: implement method for removing a node
  // TODO: implement Prim
  // TODO: implement Bellman-Ford
  // TODO: implement printGraph function that generates a file written using the
  // dot format
};
