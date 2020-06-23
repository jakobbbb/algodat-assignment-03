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
  // TODO
  ++size_;
  return m;
}

Node* MinHeap::extract_smallest() {
  if (nullptr == root_)
    return nullptr;
  auto smallest = root_->node;
  // TODO
  --size_;
  return smallest;
}

bool MinHeap::contains(Node* n) const {
  return contains(n, root_);
}

bool MinHeap::contains(Node* n, MinHeapNode* start) const {
  if (nullptr == n || nullptr == start)
    return false;
  if (start->node == n)
    return true;
  return contains(n, start->left) || contains(n, start->right);
}

bool MinHeap::empty() const {
  return 0 == size_;
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
  // prepare graph
  auto root = nodes_.front();
  root->key = 0;
  for (auto u : nodes_) {
    u->key = INT_MAX;
    u->parent = nullptr;
  }

  // prepare min heap
  auto queue = MinHeap{};
  for (auto u : nodes_)
    queue.add(u);

  while (!queue.empty()) {
    auto u = queue.extract_smallest();
    for (auto [v, w] : u->adjacent) {
      if (queue.contains(v) && w < v->key) {
        v->parent = u;
        v->key = w;
      }
    }
  }
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
