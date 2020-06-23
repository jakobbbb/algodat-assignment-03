#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <climits>
#include <map>
#include <string>
#include <vector>

// YOU CAN USE ONLY THE VECTORS, STRINGS AND MAPS FOR THIS ASSIGNMENT!

struct Node {
  std::string label;
  std::map<Node*, int> adjacent;  // ptr to adjacent node -> weight

  /**
   * Use in Prim algorithm:  The Node from which this Node was discovered.
   */
  Node* prim_parent = nullptr;
  /**
   * Use in Prim algorithm:  Weight of edge from `prim_parent_` to `*this`.
   */
  int prim_key = INT_MAX;

 public:
  Node(std::string label);
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

  void print(std::ostream& os, bool is_directed) const;
};

struct MinHeapNode {
  Node* node;
  MinHeapNode* parent = nullptr;
  MinHeapNode* left = nullptr;
  MinHeapNode* right = nullptr;

  MinHeapNode(Node* node);

  // TODO: implement additional constructors??
};

/**
 * Binary min heap for use in Prim algorithm.
 */
class MinHeap {
 private:
  MinHeapNode* root_ = nullptr;
  std::size_t size_ = 0;

 public:
  /**
   * Add a `Node` as a `MinHeapNode`
   */
  MinHeapNode* add(Node* n);

  /**
   * Remove a `Node`.
   */
  void remove(Node* n);

  /**
   * TODO: implement method for restructuring the min-priority Queue
   */
  void restructure_queue();

  /**
   * Extract the smallest element, i. e. retrieve and remove it while keeping
   * the min heap intact.
   */
  Node* extract_smallest();

  /**
   * True iff n is contained in the heap.
   */
  bool contains(Node* n) const;
  bool contains(Node* n, MinHeapNode* start) const;

  /**
   * True iff the heap is empty.
   */
  bool empty() const;
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

  /**
   * Prim algorithm.
   */
  void prim();
  // TODO: implement Bellman-Ford

  // TODO: implement printGraph function that generates a file written using the
  // dot format
  void print(std::ostream& os) const;

  std::size_t size() const;
};
#endif  // GRAPH_HPP
