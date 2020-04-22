#include "conflict_graph.h"

#include <catch2/catch.hpp>
#include <iterator>
#include <sstream>

#include "operation.h"

TEST_CASE("Conflict graph can be created", "[ConflictGraph]") {
  Graph<TransactionId> expected;
  expected.InsertEdge(1, 2);
  expected.InsertEdge(2, 3);
  expected.InsertEdge(3, 1);

  std::stringstream stream{"w 1 x r 2 x w 2 y r 3 y w 3 z r 1 z"};
  auto result = CreateConflictGraph(std::istream_iterator<Operation>(stream),
                                    std::istream_iterator<Operation>());

  REQUIRE(expected == result);
}

TEST_CASE("Self loops are not inserted into the graph", "[ConflictGraph]") {
  Graph<TransactionId> expected;

  std::stringstream stream{"r 1 x w 1 x"};
  auto result = CreateConflictGraph(std::istream_iterator<Operation>(stream),
                                    std::istream_iterator<Operation>());

  REQUIRE(expected == result);
}
