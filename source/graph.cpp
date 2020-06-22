#include "graph.hpp"
#include <iostream>

/* NODE */

Node::Node(std::string label, Node* parent, int distance)
    : label_{label}, parent_{parent}, distance_{distance} {}

Node::~Node() {}  // TODO

bool Node::operator==(Node const& rhs) const {
  return label_ == rhs.label_;  // TODO is this enough?
}

void Node::connect(Node* rhs, int weight) {
  adjacent_.insert(std::make_pair(rhs, weight));
}

void Node::disconnect(Node* rhs) {
  adjacent_.erase(rhs);
}

void Node::print(std::ostream& os) const {
  os << "  ";  // indent nodes
  os << "\"" << label_ << "\" -> {";
  for (auto adj : adjacent_) {
    os << "\"" << adj.first->label_ << "\", ";
  }
  os << "};\n";
}

/* MINHEAPNODE */


/* MINHEAP */

MinHeap::MinHeap() {} // TODO

/* GRAPH */

Graph::Graph(bool is_directed)
    : is_directed_(is_directed), min_prio_queue_{new MinHeap} {}

Graph::~Graph() {}  // TODO

void Graph::add(Node n) {
  nodes_.push_back(n);
}

void Graph::remove(Node n) {
  for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
    if (n == *it) {
      nodes_.erase(it);
      return;
    }
  }
}

void Graph::print(std::ostream& os) const {
  os << (is_directed_ ? "digraph" : "graph");
  os << "{\n";
  for (auto const& n : nodes_) n.print(os);
  os << "}\n";
}
