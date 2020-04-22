#ifndef SERIALIZABILITY_CHECKER_SRC_GRAPH_H_
#define SERIALIZABILITY_CHECKER_SRC_GRAPH_H_

#include <unordered_map>
#include <unordered_set>

template <typename Node>
class Graph {
 public:
  void InsertEdge(Node from, Node to) { adjacency_list_[from].insert(to); }

  // Checks for cycle by performing depth-first search and looking for back
  // edges. Code idea from https://stackoverflow.com/a/53995651.
  bool HasCycle() {
    std::unordered_set<Node> discovered;
    std::unordered_set<Node> finished;

    for (const auto &[node, _] : adjacency_list_) {
      if (finished.find(node) == finished.end()) {
        if (HasCycleVisit(node, discovered, finished)) {
          return true;
        }
      }
    }
    return false;
  }

  bool operator==(const Graph &rhs) const {
    return adjacency_list_ == rhs.adjacency_list_;
  }

  bool operator!=(const Graph &rhs) const { return !(rhs == *this); }

 private:
  bool HasCycleVisit(Node node, std::unordered_set<Node> &discovered,
                     std::unordered_set<Node> &finished) {
    discovered.insert(node);

    for (auto neighbor : adjacency_list_[node]) {
      if (discovered.find(neighbor) != discovered.end()) {
        // found back edge (= cycle) from node to neighbor
        return true;
      } else if (finished.find(neighbor) == finished.end()) {
        if (HasCycleVisit(neighbor, discovered, finished)) {
          return true;
        }
      }
    }

    discovered.erase(node);
    finished.insert(node);

    return false;
  }

  std::unordered_map<Node, std::unordered_set<Node>> adjacency_list_;
};

#endif  // SERIALIZABILITY_CHECKER_SRC_GRAPH_H_
