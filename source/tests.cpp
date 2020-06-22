#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "graph.hpp"

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
    g.add(baz);
    REQUIRE(3 == g.size());
    REQUIRE_NOTHROW(g.print(std::cout));
  }

  GIVEN("an empty digraph") {
    Graph g{true};
    REQUIRE_NOTHROW(g.print(std::cout));
    // TODO
  }
}
