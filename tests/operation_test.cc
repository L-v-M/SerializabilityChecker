#include "operation.h"

#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("Operations can be deserialized", "[Operation]") {
  Operation operation;
  std::stringstream stream{"w 1 x"};
  stream >> operation;
  REQUIRE(stream);
  REQUIRE(operation.GetAction() == Action::kWrite);
  REQUIRE(operation.GetTransactionId() == 1);
  REQUIRE(operation.GetDataItem() == "x");
}
