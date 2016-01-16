/**
 * This file copyright (c) 2011-2015, Quickstep Technologies LLC.
 * Copyright (c) 2015, Pivotal Software, Inc.
 * All rights reserved.
 * See file CREDITS.txt for details.
 **/

#ifndef QUICKSTEP_TYPES_OPERATIONS_UNARY_OPERATIONS_ARITHMETIC_UNARY_OPERATIONS_HPP_
#define QUICKSTEP_TYPES_OPERATIONS_UNARY_OPERATIONS_ARITHMETIC_UNARY_OPERATIONS_HPP_

#include "types/TypedValue.hpp"
#include "types/operations/unary_operations/UnaryOperation.hpp"
#include "types/operations/unary_operations/UnaryOperationID.hpp"
#include "utility/Macros.hpp"

namespace quickstep {

class Type;

/** \addtogroup Types
 *  @{
 */

/**
 * @brief A UnaryOperation which applies to and yields numeric values.
 **/
class ArithmeticUnaryOperation : public UnaryOperation {
 public:
  bool canApplyToType(const Type &type) const override;

  const Type* resultTypeForArgumentType(const Type &type) const override;

  const Type* pushDownTypeHint(const Type *type_hint) const override;

 protected:
  explicit ArithmeticUnaryOperation(const UnaryOperationID operation_id)
      : UnaryOperation(operation_id) {
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(ArithmeticUnaryOperation);
};

/**
 * @brief The UnaryOperation for negation.
 **/
class NegateUnaryOperation : public ArithmeticUnaryOperation {
 public:
  /**
   * @brief Get a reference to the singleton instance of this Operation.
   *
   * @return A reference to the singleton instance of this Operation.
   **/
  static const NegateUnaryOperation& Instance() {
    static NegateUnaryOperation instance;
    return instance;
  }

  const Type* fixedNullableResultType() const override {
    return nullptr;
  }

  bool resultTypeIsPlausible(const Type &result_type) const override;

  TypedValue applyToChecked(const TypedValue &argument,
                            const Type &argument_type) const override;

  UncheckedUnaryOperator* makeUncheckedUnaryOperatorForType(const Type &type) const override;

 private:
  NegateUnaryOperation()
      : ArithmeticUnaryOperation(UnaryOperationID::kNegate) {
  }

  DISALLOW_COPY_AND_ASSIGN(NegateUnaryOperation);
};

/** @} */

}  // namespace quickstep

#endif  // QUICKSTEP_TYPES_OPERATIONS_UNARY_OPERATIONS_ARITHMETIC_UNARY_OPERATIONS_HPP_
