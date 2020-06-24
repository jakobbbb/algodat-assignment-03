#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
#include "graph.hpp"

/**
 * Helper function to generate a graph of size `n_elements`, where each pair of
 * elements has a chance `p` of being connected with a random weight between 1
 * and max_weight.
 */
Graph make_graph(bool is_directed, int n_elements, int max_weight, float p) {
  std::srand(0);
  Graph g{is_directed};
  std::vector<Node*> nodes;
  for (int i = 0; i < n_elements; ++i) {
    Node n{"n" + std::to_string(i)};
    Node* n_ptr = g.add(n);
    nodes.push_back(n_ptr);
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
  return g;
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
    auto g = make_graph(false, size, 15, 0.01f);
    REQUIRE(size == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
  }

  GIVEN("an empty digraph") {
    Graph g{true};
    REQUIRE_NOTHROW(g.print(std::cout));
    // TODO
  }
}

SCENARIO("bellman-ford", "[bellman]") {
  GIVEN("a non-empty graph") {
    Graph g{false};
    Node foo{"foo"};
    Node bar{"bar"};
    Node baz{"baz"};
    auto foo_ptr = g.add(foo);
    auto bar_ptr = g.add(bar);
    auto baz_ptr = g.add(baz);
    foo_ptr->connect(bar_ptr, 3);
    foo_ptr->connect(baz_ptr, 5);
    REQUIRE(3 == g.size());
    std::cout << "----------\n";
    g.print(std::cout);
    std::cout << "----------\n";
    std::cout << (g.bellmann_ford(foo_ptr) ? "t" : "f");
    g.print(std::cout);
  }
}
