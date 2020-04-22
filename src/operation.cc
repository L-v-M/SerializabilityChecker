#include "operation.h"

#include <utility>

Operation::Operation(Action action, TransactionId transaction_id,
                     DataItem data_item)
    : action_(action),
      transaction_id_(transaction_id),
      data_item_(std::move(data_item)) {}

Action Operation::GetAction() const { return action_; }

TransactionId Operation::GetTransactionId() const { return transaction_id_; }

const DataItem &Operation::GetDataItem() const { return data_item_; }

std::istream &operator>>(std::istream &stream, Operation &operation) {
  char action_literal;
  if (stream >> action_literal >> operation.transaction_id_ >>
      operation.data_item_) {
    operation.action_ = action_literal == 'r' ? Action::kRead : Action::kWrite;
  } else {
    stream.setstate(std::ios_base::failbit);
  }
  return stream;
}
