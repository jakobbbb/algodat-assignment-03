#include "graph.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/* NODE */

Node::Node(std::string label) : label{label} {}

Node::~Node() {}  // TODO?

bool Node::operator==(Node const& rhs) const {
  return label == rhs.label;  // TODO is this enough?
}

void Node::connect(Node* rhs, int weight) {
  assert(INFTY > weight);
  adjacent.insert(std::make_pair(rhs, weight));
}

void Node::disconnect(Node* rhs) {
  adjacent.erase(rhs);
}

void Node::print(std::ostream& os, bool directed) const {
  std::string sep = directed ? "->" : "--";

  for (auto [other, weight] : adjacent) {
    std::string color = (other->parent == this) ? "blue" : "black";
    os << "  "  // indent
       << "\"" << *this << "\" "
       << sep
       << " \"" << *other << "\" "
       << "["
       << "label=" << weight << ", "
       << "color=" << color
       << "];\n";
  }
}

std::ostream& operator<<(std::ostream& os, Node const& n) {
  os << n.label << "\\n(";
  if (INFTY == n.key)
    os << "inf";
  else
    os << n.key;
  os << ")";
  return os;
}

/* MINHEAP */

int MinHeap::parent(int i) const {
  return i / 2;  // floor is implicit
}

int MinHeap::left(int i) const {
  return 2 * i;
}

int MinHeap::right(int i) const {
  return 2 * i + 1;
}

void MinHeap::add(Node* n) {
  nodes_.push_back(n);
  // TODO
  assert(valid());
}

Node* MinHeap::extract_smallest() {
  if (empty())
    return nullptr;
  auto smallest = nodes_.front();
  // TODO
  assert(valid());
  return smallest;
}

bool MinHeap::contains(Node* n) const {
  for (auto node : nodes_) {
    if (node == n)
      return true;
  }
  return false;
}

bool MinHeap::empty() const {
  return nodes_.empty();
}

std::size_t MinHeap::size() const {
  return nodes_.size();
}

bool MinHeap::valid() const {
  if (nodes_.size() <= 2)
    return true;
  for (std::vector<Node*>::size_type i = 1; i < nodes_.size(); ++i) {
    if (nodes_[parent(i)] < nodes_[i])
      return false;
  }
  return true;
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
    u->key = INFTY;
    u->parent = nullptr;
  }

  // prepare min heap
  MinHeap queue;
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

bool Graph::bellmann_ford(Node* s) {
  // setup
  for (auto& u : nodes_) {
    u->key = INFTY;
    u->parent = nullptr;
  }
  s->key = 0;

  // attempt to relaxe all edges nodes_.size()-1 times
  for (std::size_t i = 1; i < nodes_.size(); ++i) {
    for (auto& u : nodes_) {
      for (auto [v, w] : u->adjacent) {
        relax(u, v, w);
      }
    }
  }

  // check for negative cycles
  for (auto& u : nodes_) {
    for (auto [v, w] : u->adjacent) {
      if (v->key > w + u->key)
        return false;
    }
  }
  return true;
}

void Graph::relax(Node* u, Node* v, int w) {
  if (v->key > (w + u->key)) {
    v->parent = u;
    v->key = w + u->key;
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
}
