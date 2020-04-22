#ifndef SERIALIZABILITY_CHECKER_SRC_CONFLICTGRAPH_H_
#define SERIALIZABILITY_CHECKER_SRC_CONFLICTGRAPH_H_

#include <unordered_map>
#include <unordered_set>

#include "graph.h"
#include "operation.h"

template <typename InputIt>
Graph<TransactionId> CreateConflictGraph(InputIt first, InputIt last) {
  std::unordered_map<DataItem, std::unordered_set<TransactionId>> read_by;
  std::unordered_map<DataItem, std::unordered_set<TransactionId>> written_by;

  Graph<TransactionId> conflict_graph;

  for (; first != last; ++first) {
    const Operation &current_operation = *first;

    // current_operation is in conflict with all operations that happened before
    // and wrote the same item.
    for (auto conflicting_transaction_id :
         written_by[current_operation.GetDataItem()]) {
      if (conflicting_transaction_id != current_operation.GetTransactionId()) {
        conflict_graph.InsertEdge(conflicting_transaction_id,
                                  current_operation.GetTransactionId());
      }
    }

    if (current_operation.GetAction() == Action::kWrite) {
      // current_operation is also in conflict with all operations that happened
      // before and read the same item.
      for (auto conflicting_transaction_id :
           read_by[current_operation.GetDataItem()]) {
        if (conflicting_transaction_id !=
            current_operation.GetTransactionId()) {
          conflict_graph.InsertEdge(conflicting_transaction_id,
                                    current_operation.GetTransactionId());
        }
      }

      // update data structures.
      written_by[current_operation.GetDataItem()].insert(
          current_operation.GetTransactionId());
    } else {
      read_by[current_operation.GetDataItem()].insert(
          current_operation.GetTransactionId());
    }
  }

  return conflict_graph;
}

#endif  // SERIALIZABILITY_CHECKER_SRC_CONFLICTGRAPH_H_
