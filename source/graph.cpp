#include "graph.hpp"

Node::Node(std::string label, Node* parent, int distance)
    : label_{label}, parent_{parent}, distance_{distance} {}

bool Node::operator==(Node const& rhs) const {
  return label_ == rhs.label_;  // TODO is this enough?
}

void Node::connect(Node* rhs, int weight) {
  adjacent_.insert(std::make_pair(rhs, weight));
}

void Node::disconnect(Node* rhs) {
  adjacent_.erase(rhs);
}

Graph::Graph(bool is_directed)
    : is_directed_(is_directed), min_prio_queue_{new MinHeap} {}

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
