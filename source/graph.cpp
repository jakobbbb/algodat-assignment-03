#include "graph.hpp"
#include <cassert>
#include <iostream>

/* NODE */

Node::Node(std::string label) : label{label} {}

Node::~Node() {}  // TODO?

bool Node::operator==(Node const& rhs) const {
  return label == rhs.label;  // TODO is this enough?
}

void Node::connect(Node* rhs, int weight) {
  adjacent.insert(std::make_pair(rhs, weight));
}

void Node::disconnect(Node* rhs) {
  adjacent.erase(rhs);
}

void Node::prim_update_parent(Node* parent) {
  if (nullptr == parent) {
    prim_parent_ = parent;
    prim_key_ = 0;
    return;
  }

  auto it = parent->adjacent.find(this);
  if (parent->adjacent.end() == it)
    throw "Parent is not connected!";
  auto key = it->second;
  if (key >= prim_key_)
    return;  // do not update
  prim_parent_ = parent;
  prim_key_ = it->second;
}

void Node::print(std::ostream& os, bool is_directed) const {
  std::string sep = is_directed ? "->" : "--";
  for (auto el : adjacent) {
    std::string label = el.first->label;
    int weight = el.second;
    os << "  ";  // indent
    os << "\"" << label << "\" " << sep << " ";
    os << "\"" << el.first->label << "\" ";
    os << "[weight=" << weight << ", penwidth=" << weight << "];\n";
  }
}

/* MINHEAPNODE */
MinHeapNode::MinHeapNode(Node* node) : node{node} {}

/* MINHEAP */

MinHeapNode* MinHeap::add(Node* n) {
  auto m = new MinHeapNode{n};
  if (nullptr == root_)
    root_ = m;

  return m;
}

Node* MinHeap::extract_smallest() {
  if (nullptr == root_)
    return nullptr;
  auto smallest = root_->node;
  // TODO
  return smallest;
}

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

void Graph::prim() {
  auto root = nodes_.front();
  root->prim_update_parent(nullptr);
  for (auto [child, distance] : root->adjacent)
    child->prim_update_parent(root);
  // TODO
}

void Graph::print(std::ostream& os) const {
  os << (is_directed_ ? "digraph" : "graph");
  os << " {\n";
  for (auto const& n : nodes_)
    n->print(os, is_directed_);
  os << "}\n";
}

std::size_t Graph::size() const {
  return nodes_.size();
};
