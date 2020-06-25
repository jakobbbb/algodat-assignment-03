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

void MinHeap::build(std::vector<Node*> const& nodes) {
  size_ = nodes.size();
  for (int i = size_/2; i >= 1; --i) {
  }
  // TODO
  assert(valid());
}

void MinHeap::heapify(MinHeapNode* n) {
  auto l = n->left;
  auto r = n->right;
  auto smallest = n;
  if (l->key <= size_ && l->key < n->key)
    smallest = l;
  if (r->key <= size_ && r->key < smallest->key)
    smallest =r;
  if (smallest != n) {
    exchange(n, smallest);
    heapify(smallest);
  }
}

void MinHeap::exchange(MinHeapNode* a, MinHeapNode* b) {
  std::swap(a->node, b->node);
  std::swap(a->key, b->key);
}

Node* MinHeap::extract_smallest() {
  if (empty())
    return nullptr;
  auto smallest = root_->node;
  // TODO
  throw "TODO";
  assert(valid());
  return smallest;
}

bool MinHeap::contains(Node* n) const {
  // TODO
  return false;
}

bool MinHeap::empty() const {
  return 0 == size_;
}

bool MinHeap::valid() const {
  // TODO
  return false;
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

  /* Had some trouble creating the MinHeap, so we're substituting it with a
   * simple array of nodes that gets sorted.  This, of course, drags efficiency
   * down, but allows Prim to function. */
  std::vector<Node*> queue;  // MinHeap queue;
  for (auto u : nodes_)
    queue.push_back(u);

  while (!queue.empty()) {
    std::sort(queue.begin(), queue.end(), [](Node* a, Node* b) {
      return a->key > b->key;
    });  // queue.restructure();
    auto u = queue.back();
    queue.pop_back();  // auto u = queue.extract_smallest();
    for (auto [v, w] : u->adjacent) {
      // if (queue.contains(v) && w < v->key)
      if ((std::find(queue.begin(), queue.end(), v) != queue.end()) &&
          w < v->key) {
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
