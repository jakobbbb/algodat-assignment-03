#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
#include "graph.hpp"

SCENARIO("min-heap", "[heap]") {
  std::srand(0);

  MinHeap h;
  REQUIRE(h.empty());
  REQUIRE(0 == h.size());

  std::vector<Node*> nodes;
  for (std::size_t i = 0; i < 100; ++i) {
    auto n = new Node{"n" + std::to_string(i)};
    n->key = std::rand() % 20;
    nodes.push_back(n);
  }
  MinHeap h2{nodes};
  REQUIRE(h2.valid());

  for (std::size_t i = 0; i < 100; ++i) {
    h2.extract();
    REQUIRE(h2.valid());
  }
}
/**
 * Helper function to generate a graph of size `n_elements`, where each pair of
 * elements has a chance `p` of being connected with a random weight between 1
 * and max_weight.
 */
std::pair<Graph*, std::vector<Node*>> make_graph(bool is_directed,
                                                 int n_elements,
                                                 int max_weight,
                                                 float p) {
  std::srand(0);
  auto g = new Graph{is_directed};
  std::vector<Node*> nodes;
  for (int i = 0; i < n_elements; ++i) {
    auto n = g->add({"n" + std::to_string(i)});
    nodes.push_back(n);
  }
  for (auto n : nodes) {
    for (auto m : nodes) {
      if (n == m)
        continue;
      if (std::rand() < RAND_MAX * p) {
        int weight = (std::rand() % (max_weight - 1)) + 1;
        n->connect(m, weight);
      }
    }
  }
  return std::make_pair(g, nodes);
}

SCENARIO("print a graph", "[graph]") {
  GIVEN("an empty graph") {
    Graph g{false};
    REQUIRE(0 == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
    WHEN("adding a node") {
      Node foo{"foo"};
      g.add(foo);
      REQUIRE(1 == g.size());
      REQUIRE_NOTHROW(g.print(std::cout));
    }
  }
  GIVEN("a non-empty graph") {
    Graph g{false};
    Node foo{"foo"};
    Node bar{"bar"};
    Node baz{"baz"};
    auto foo_ptr = g.add(foo);
    auto bar_ptr = g.add(bar);
    g.add(baz);
    foo_ptr->connect(bar_ptr, 3);
    REQUIRE(3 == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
  }
  GIVEN("a large graph") {
    const int size = 200;
    auto g = make_graph(false, size, 15, 0.01f).first;
    REQUIRE(size == g->size());
    REQUIRE_NOTHROW(g->print(std::cout));
  }

  GIVEN("an empty digraph") {
    Graph g{true};
    REQUIRE_NOTHROW(g.print(std::cout));
    // TODO
  }
}

SCENARIO("bellman-ford", "[bellman]") {
  GIVEN("the digraph presented in the exercise") {
    Graph g{true};

    auto a = g.add({"a"});
    auto b = g.add({"b"});
    auto c = g.add({"c"});
    auto d = g.add({"d"});
    auto e = g.add({"e"});
    auto f = g.add({"f"});

    a->connect(e, 7);
    a->connect(f, 5);
    b->connect(a, 1);
    b->connect(c, 3);
    c->connect(d, 9);
    d->connect(c, 3);
    d->connect(e, 2);
    d->connect(f, 1);
    e->connect(b, 2);
    e->connect(c, 4);
    f->connect(e, 2);
    REQUIRE(g.bellmann_ford(a));
  }

  GIVEN("a digraph") {
    const int size = 20;
    auto [g, nodes] = make_graph(true, size, 15, 0.1f);
    REQUIRE(size == g->size());
    for (auto n : nodes) {
      REQUIRE_NOTHROW(g->bellmann_ford(n));
      REQUIRE_NOTHROW(g->print(std::cout));
    }
  }

  GIVEN("a large digraph") {
    const int size = 200;
    auto [g, nodes] = make_graph(true, size, 15, 0.1f);
    REQUIRE(size == g->size());
    REQUIRE_NOTHROW(g->bellmann_ford(nodes.front()));
  }
}

SCENARIO("prim", "[prim]") {
  GIVEN("the graph presented in the exercise") {
    Graph g{false};

    auto a = g.add({"a"});
    auto b = g.add({"b"});
    auto c = g.add({"c"});
    auto d = g.add({"d"});
    auto e = g.add({"e"});
    auto f = g.add({"f"});

    a->connect(e, 7);
    a->connect(f, 5);
    b->connect(a, 1);
    b->connect(c, 3);
    c->connect(d, 9);
    d->connect(e, 2);
    d->connect(f, 1);
    e->connect(b, 2);
    e->connect(c, 4);
    f->connect(e, 2);
    REQUIRE_NOTHROW(g.prim());
  }

  GIVEN("a graph") {
    const int size = 20;
    auto [g, nodes] = make_graph(false, size, 15, 0.1f);
    REQUIRE(size == g->size());
    REQUIRE_NOTHROW(g->prim());
    REQUIRE_NOTHROW(g->print(std::cout));
  }

  GIVEN("a large graph") {
    const int size = 200;
    auto [g, nodes] = make_graph(false, size, 15, 0.1f);
    REQUIRE_NOTHROW(g->prim());
    REQUIRE_NOTHROW(g->print(std::cout));
  }
}
