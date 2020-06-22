#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>
#include "graph.hpp"

Graph make_graph(bool is_directed, int n_elements, float p) {
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
      if (n == m) continue;
      if (std::rand() < RAND_MAX * p) {
        n->connect(m, (std::rand() % 14) + 1);
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
    auto g = make_graph(false, size, 0.01f);
    REQUIRE(size == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
  }

  GIVEN("an empty digraph") {
    Graph g{true};
    REQUIRE_NOTHROW(g.print(std::cout));
    // TODO
  }
}
