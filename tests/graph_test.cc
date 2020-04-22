#include "graph.h"

#include <catch2/catch.hpp>

TEST_CASE("Cycles can be detected in graphs", "[graph]") {
  Graph<int> graph;
  graph.InsertEdge(1, 2);
  graph.InsertEdge(2, 3);
  graph.InsertEdge(3, 4);

  SECTION("Returns false when there is no cycle") {
    REQUIRE(!graph.HasCycle());

    graph.InsertEdge(1, 3);
    REQUIRE(!graph.HasCycle());

    graph.InsertEdge(2, 4);
    REQUIRE(!graph.HasCycle());
  }

  SECTION("Returns true when there is a cycle") {
    graph.InsertEdge(4, 1);
    REQUIRE(graph.HasCycle());

    graph.InsertEdge(2, 1);
    REQUIRE(graph.HasCycle());
  }
}