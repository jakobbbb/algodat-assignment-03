#include "graph.hpp"
#include <cassert>
#include <iostream>

/* NODE */

Node::Node(std::string label, Node* parent, int distance)
    : label_{label}, parent_{parent}, distance_{distance} {}

Node::~Node() {}  // TODO?

bool Node::operator==(Node const& rhs) const {
  return label_ == rhs.label_;  // TODO is this enough?
}

void Node::connect(Node* rhs, int weight) {
  adjacent_.insert(std::make_pair(rhs, weight));
}

void Node::disconnect(Node* rhs) {
  adjacent_.erase(rhs);
}

void Node::print(std::ostream& os, bool is_directed) const {
  std::string sep = is_directed ? "->" : "--";
  for (auto el : adjacent_) {
    std::string label = el.first->label_;
    int weight = el.second;
    os << "  ";  // indent
    os << "\"" << label_ << "\" " << sep << " ";
    os << "\"" << el.first->label_ << "\" ";
    os << "[weight=" << weight << ", penwidth=" << weight << "];\n";
  }
}

/* MINHEAPNODE */
MinHeapNode::MinHeapNode(Node* node) : node{node} {}

/* MINHEAP */

MinHeap::MinHeap() {}  // TODO

/* GRAPH */

Graph::Graph(bool is_directed)
    : is_directed_(is_directed), min_prio_queue_{new MinHeap} {}

Graph::~Graph() {
  for (auto n : nodes_)
    remove(n);
}

Node* Graph::add(Node n) {
  auto nn = new Node{n};
  nodes_.push_back(nn);
  return nn;
}

void Graph::remove(Node* n) {
  for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
    if (n == *it) {
      nodes_.erase(it);
      assert(nullptr != n);
      delete n;
      return;
    }
  }
}

std::size_t Graph::size() const {
  return nodes_.size();
};

void Graph::print(std::ostream& os) const {
  os << (is_directed_ ? "digraph" : "graph");
  os << " {\n";
  for (auto const& n : nodes_)
    n->print(os, is_directed_);
  os << "}\n";
}
