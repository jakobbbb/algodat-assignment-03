#include "graph.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/* NODE */

Node::Node(std::string label) : label{label} {}

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
       << "\"" << *this << "\" " << sep << " \"" << *other << "\" "
       << "["
       << "label=" << weight << ", "
       << "color=" << color << "];\n";
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

int parent(int i) {
  return i / 2;  // floor is implicit
}

int left(int i) {
  return 2 * i;
}

int right(int i) {
  return (2 * i) + 1;
}

MinHeap::MinHeap(std::vector<Node*> const& nodes) {
  for (auto& n : nodes)
    insert(n);
}

void MinHeap::decrease_key(int i, int key) {
  if (key > nodes_[i]->key)
    throw "new key cannot be larger than current key";
  nodes_[i]->key = key;
  while (i > 0 && nodes_[parent(i)]->key > nodes_[i]->key) {
    swap(i, parent(i));
    i = parent(i);
  }
}

void MinHeap::insert(Node* n) {
  nodes_.push_back(n);
  decrease_key(nodes_.size() - 1, n->key);
}

int MinHeap::key(int i) const {
  assert(i < size());
  return nodes_[i]->key;
}

void MinHeap::heapify(int i) {
  auto l = left(i);
  auto r = right(i);
  auto smallest = i;
  if (l < size() && key(l) < key(i))
    smallest = l;
  if (r < size() && key(r) < key(smallest))
    smallest = r;
  if (smallest != i) {
    swap(i, smallest);
    heapify(smallest);
  }
}

void MinHeap::swap(int a, int b) {
  auto tmp = nodes_[a];
  nodes_[a] = nodes_[b];
  nodes_[b] = tmp;
}

Node* MinHeap::extract() {
  if (empty())
    throw "Cannot extract from empty heap!";
  auto smallest = nodes_.front();
  nodes_[0] = nodes_.back();
  nodes_.pop_back();
  heapify(0);
  return smallest;
}

bool MinHeap::contains(Node* n) const {
  if (empty())
    return false;
  return std::find(nodes_.begin(), nodes_.end(), n) != nodes_.end();
}

std::size_t MinHeap::size() const {
  return nodes_.size();
}

bool MinHeap::empty() const {
  return 0 == size();
}

/* GRAPH */

Graph::Graph(bool directed) : directed_(directed) {}

Graph::~Graph() {
  for (auto n : nodes_)
    remove(n);
}

Node* Graph::add(Node const& n) {
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

  MinHeap queue{nodes_};

  while (!queue.empty()) {
    auto u = queue.extract();
    for (auto [v, w] : u->adjacent) {
      if (queue.contains(v) && w < v->key) {
        v->parent = u;
        v->key = w;
      }
    }
  }
}

bool Graph::bellmann_ford(Node* s) {
  // setup nodes
  for (auto& u : nodes_) {
    u->key = INFTY;
    u->parent = nullptr;
  }
  s->key = 0;

  // attempt to relax all edges nodes_.size()-1 times
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
  if (v->key > (w + u->key)) {  // there is a better way of reaching v
    v->parent = u;
    v->key = w + u->key;
  }
}

void Graph::print(std::ostream& os) const {
  os << (directed_ ? "digraph" : "graph");
  os << " {\n";
  for (auto const& n : nodes_)
    n->print(os, directed_);
  os << "}\n";
}

std::size_t Graph::size() const {
  return nodes_.size();
}
