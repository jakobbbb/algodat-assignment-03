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
    auto n = new Node{"n" + std::to_string(i), nullptr, i};
    g.add(n);
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
  return g;
}

SCENARIO("print a graph", "[graph]") {
  GIVEN("an empty graph") {
    Graph g{false};
    REQUIRE(0 == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
    WHEN("adding a node") {
      auto foo = new Node{"foo", nullptr, 0};
      g.add(foo);
      REQUIRE(1 == g.size());
      REQUIRE_NOTHROW(g.print(std::cout));
    }
  }
  GIVEN("a non-empty graph") {
    Graph g{false};
    auto foo = new Node{"foo", nullptr, 0};
    auto bar = new Node{"bar", nullptr, 0};
    foo->connect(bar, 3);
    auto baz = new Node{"baz", nullptr, 0};
    g.add(foo);
    g.add(bar);
    g.add(baz);
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
