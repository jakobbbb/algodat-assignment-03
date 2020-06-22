#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "graph.hpp"

SCENARIO("print a graph", "[graph]") {
  GIVEN("an empty graph") {
    Graph g{false};
    REQUIRE_NOTHROW(g.print(std::cout));
  }

  GIVEN("an empty digraph") {
    Graph g{true};
    REQUIRE_NOTHROW(g.print(std::cout));
  }
}
