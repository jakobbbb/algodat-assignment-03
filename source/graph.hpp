#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <string>
#include <vector>

// YOU CAN USE ONLY THE VECTORS, STRINGS AND MAPS FOR THIS ASSIGNMENT!

class Node {
 private:
  /* data */
  std::string label_;
  std::map<Node, int> adjacent_;  // the int is for the weight od the egde
  Node* parent_;
  int distance_;  // aka key

 public:
  Node(std::string label, Node* parent, int distance);
  ~Node();

  // TODO: implement additional constructors?

  /**
   * Add a connection between this node and another.
   */
  void connect(Node* rhs);

  /**
   * Remove connection between this node and another.
   */
  void disconnect(Node* rhs);

  // TODO: implement methods for manipulating the parent and distance
};

class MinHeapNode {
 private:
  /* data */
  Node* node_;
  MinHeapNode* parent_;
  MinHeapNode* left_;
  MinHeapNode* right_;

 public:
  MinHeapNode(Node* node,
              MinHeapNode* parent,
              MinHeapNode* left,
              MinHeapNode* right);
  ~MinHeapNode();

  // TODO: implement additional constructors
};

class MinHeap {
 private:
  MinHeapNode* root_;

 public:
  MinHeap(/* args */);
  ~MinHeap();
  // TODO: implement method for restructuring the min-priority Queue
  void restructure_queue();
  // TODO: implement method for extracting the smaller element from the
  // min-priority Queue
  MinHeapNode* smallest();
};

class Graph {
 private:
  std::vector<Node> nodes_;
  MinHeap* min_prio_queue_;
  bool is_directed_;

 public:
  Graph(bool is_directed);
  ~Graph();

  // TODO: implement additional constructors

  /**
   * Add a node to the graph.
   */
  void add(Node* n);

  /**
   * Remove a node from the graph.
   */
  void remove(Node* n);

  // TODO: implement Prim
  // TODO: implement Bellman-Ford
  void print(std::ostream& os);
  // TODO: implement printGraph function that generates a file written using the
  // dot format
};
#endif  // GRAPH_HPP
