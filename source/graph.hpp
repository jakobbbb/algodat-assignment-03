#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>
#include <map>
#include <string>
#include <vector>

#define INFTY 99999

// YOU CAN USE ONLY THE VECTORS, STRINGS AND MAPS FOR THIS ASSIGNMENT!

struct Node;
struct MinHeapNode;
class MinHeap;
class Graph;

struct Node {
  std::string label;
  std::map<Node*, int> adjacent;  // ptr to adjacent node -> weight

  Node(std::string label);
  ~Node();

  bool operator==(Node const& rhs) const;

  /**
   * Used in Prim and Bellman–Ford.
   * The Node from which this Node was discovered.
   */
  Node* parent = nullptr;
  /**
   * Weight of edge from `parent` to this Node.
   * Used in Prim and Bellman–Ford.
   */
  int key = INFTY;


  /**
   * Add a connection between this node and another.
   */
  void connect(Node* rhs, int weight);

  /**
   * Remove connection between this node and another.
   */
  void disconnect(Node* rhs);

  void print(std::ostream& os, bool directed) const;
};

std::ostream& operator<<(std::ostream& os, Node const& n);

struct MinHeapNode {
  Node* node;
  int key;

  MinHeapNode(Node* node, int key);
};

/**
 * Binary min heap for use in Prim algorithm.
 */
class MinHeap {
 private:
  std::vector<MinHeapNode*> nodes;

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
  // void prim();

  /**
   * Bellman–Ford algorithm.
   * s: chosen source
   * Returns false if no answer could be found, e. g. due to the graph being
   * cyclic.
   */
  bool bellmann_ford(Node* s);
  void relax(Node* u, Node* v, int w);

  // TODO: implement printGraph function that generates a file written using the
  // dot format
  void print(std::ostream& os) const;

  std::size_t size() const;
};
#endif  // GRAPH_HPP
