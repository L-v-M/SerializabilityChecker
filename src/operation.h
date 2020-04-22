#ifndef SERIALIZABILITY_CHECKER_SRC_OPERATION_H_
#define SERIALIZABILITY_CHECKER_SRC_OPERATION_H_

#include <istream>
#include <string>

enum class Action { kRead, kWrite };

using TransactionId = int;

using DataItem = std::string;

class Operation {
 public:
  Operation() = default;
  Operation(Action action, TransactionId transaction_id, DataItem data_item);

  [[nodiscard]] Action GetAction() const;
  [[nodiscard]] TransactionId GetTransactionId() const;
  [[nodiscard]] const DataItem &GetDataItem() const;

 private:
  friend std::istream &operator>>(std::istream &stream, Operation &operation);

  Action action_{Action::kRead};
  TransactionId transaction_id_{};
  DataItem data_item_{};
};

#endif  // SERIALIZABILITY_CHECKER_SRC_OPERATION_H_
