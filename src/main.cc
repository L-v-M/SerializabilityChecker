#include <iostream>
#include <iterator>
#include <sstream>

#include "conflict_graph.h"
#include "operation.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "usage: serializability-checker history";
    return 1;
  }

  std::stringstream stream;
  for (int i = 1; i != argc; ++i) {
    stream << argv[i] << " ";
  }

  auto conflict_graph =
      CreateConflictGraph(std::istream_iterator<Operation>(stream),
                          std::istream_iterator<Operation>());

  std::cout << std::boolalpha << !conflict_graph.HasCycle() << "\n";

  return 0;
}
