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
  std::map<Node*, int> adjacent_;  // ptr to adjacent node -> weight
  Node* parent_;
  int distance_;  // aka key

 public:
  Node(std::string label, Node* parent, int distance);
  ~Node();

  // TODO: implement additional constructors?

  bool operator==(Node const& rhs) const;

  /**
   * Add a connection between this node and another.
   */
  void connect(Node* rhs, int weight);

  /**
   * Remove connection between this node and another.
   */
  void disconnect(Node* rhs);

  // TODO: implement methods for manipulating the parent and distance

  void print(std::ostream& os, bool is_directed) const;
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
  bool is_directed_;
  std::vector<Node*> nodes_;
  MinHeap* min_prio_queue_;

 public:
  Graph(bool is_directed);
  ~Graph();

  // TODO: implement additional constructors

  /**
   * Add a node to the graph.
   */
  Node* add(Node n);

  /**
   * Remove a node from the graph.
   * This also deletes the node.
   */
  void remove(Node* n);

  // TODO: implement Prim
  // TODO: implement Bellman-Ford

  // TODO: implement printGraph function that generates a file written using the
  // dot format
  void print(std::ostream& os) const;

  std::size_t size() const;
};
#endif  // GRAPH_HPP
