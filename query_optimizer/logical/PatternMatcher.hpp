/**
 * This file copyright (c) 2011-2015, Quickstep Technologies LLC.
 * All rights reserved.
 * See file CREDITS.txt for details.
 **/

#ifndef QUICKSTEP_QUERY_OPTIMIZER_LOGICAL_PATTERN_MATCHER_HPP_
#define QUICKSTEP_QUERY_OPTIMIZER_LOGICAL_PATTERN_MATCHER_HPP_

#include <memory>
#include <type_traits>

#include "query_optimizer/logical/LogicalType.hpp"

namespace quickstep {
namespace optimizer {
namespace logical {

class Aggregate;
class BinaryJoin;
class CopyFrom;
class CreateTable;
class DeleteTuples;
class DropTable;
class Filter;
class HashJoin;
class InsertTuple;
class Join;
class MultiwayCartesianJoin;
class NestedLoopsJoin;
class Project;
class SharedSubplanReference;
class Sort;
class TableReference;
class TopLevelPlan;
class UpdateTable;

/** \addtogroup OptimizerLogical
 *  @{
 */

/**
 * @brief Templated matcher for each Logical node class.
 *
 * @param LogicalClass The logical class for the logical node to be matched with.
 * @param logical_types All the logical types of the logical class.
 */
template <class LogicalClass, LogicalType... logical_types>
class SomeLogicalNode {
 public:
  /**
   * @brief Checks whether the object managed in \p logical is an instance
   *        of the template argument LogicalClass by checking whether
   *        it is one of types in the given template arguments logical_types.
   *
   * @param logical The logical node to be checked.
   * @return True for a match; otherwise false.
   */
  template <class OtherLogicalClass>
  static bool Matches(const std::shared_ptr<const OtherLogicalClass> &logical) {
    for (const LogicalType logical_type : kLogicalTypes) {
      if (logical->getLogicalType() == logical_type) {
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Checks whether the object managed in \p logical is an instance
   *        of the template argument LogicalClass by checking whether
   *        it is one of types in the given template arguments logical_types,
   *        If true, it additionally casts \p logical to a std::shared_ptr
   *        \p cast_logical of the template argument LogicalClass.
   *
   * @param logical The logical node to be checked.
   * @param cast_logical The cast logical node.
   * @return True if the object managed in \p logical is an instance of LogicalClass.
   */
  template <class OtherLogicalClass>
  static bool MatchesWithConditionalCast(const std::shared_ptr<const OtherLogicalClass> &logical,
                                         std::shared_ptr<const LogicalClass> *cast_logical) {
    bool is_match = Matches(logical);
    if (is_match) {
      *cast_logical = std::static_pointer_cast<const LogicalClass>(logical);
    }
    return is_match;
  }

 private:
  constexpr static LogicalType kLogicalTypes[] = {logical_types...};
};

template <class LogicalClass, LogicalType... logical_types>
constexpr LogicalType SomeLogicalNode<LogicalClass, logical_types...>::kLogicalTypes[];

// Specializations for all Logical classes.

using SomeAggregate = SomeLogicalNode<Aggregate, LogicalType::kAggregate>;
using SomeBinaryJoin = SomeLogicalNode<BinaryJoin,
                                       LogicalType::kHashJoin,
                                       LogicalType::kNestedLoopsJoin>;
using SomeCopyFrom = SomeLogicalNode<CopyFrom, LogicalType::kCopyFrom>;
using SomeCreateTable = SomeLogicalNode<CreateTable, LogicalType::kCreateTable>;
using SomeDeleteTuples = SomeLogicalNode<DeleteTuples, LogicalType::kDeleteTuples>;
using SomeDropTable = SomeLogicalNode<DropTable, LogicalType::kDropTable>;
using SomeFilter = SomeLogicalNode<Filter, LogicalType::kFilter>;
using SomeHashJoin = SomeLogicalNode<HashJoin, LogicalType::kHashJoin>;
using SomeInsertTuple = SomeLogicalNode<InsertTuple, LogicalType::kInsertTuple>;
using SomeJoin = SomeLogicalNode<Join,
                                 LogicalType::kHashJoin,
                                 LogicalType::kMultiwayCartesianJoin,
                                 LogicalType::kNestedLoopsJoin>;
using SomeMultiwayCartesianJoin = SomeLogicalNode<MultiwayCartesianJoin, LogicalType::kMultiwayCartesianJoin>;
using SomeNestedLoopsJoin = SomeLogicalNode<NestedLoopsJoin, LogicalType::kNestedLoopsJoin>;
using SomeProject = SomeLogicalNode<Project, LogicalType::kProject>;
using SomeSharedSubplanReference = SomeLogicalNode<SharedSubplanReference, LogicalType::kSharedSubplanReference>;
using SomeSort = SomeLogicalNode<Sort, LogicalType::kSort>;
using SomeTableReference = SomeLogicalNode<TableReference, LogicalType::kTableReference>;
using SomeTopLevelPlan = SomeLogicalNode<TopLevelPlan, LogicalType::kTopLevelPlan>;
using SomeUpdateTable = SomeLogicalNode<UpdateTable, LogicalType::kUpdateTable>;

/** @} */

}  // namespace logical
}  // namespace optimizer
}  // namespace quickstep

#endif /* QUERY_PLANNER_LOGICAL_PATTERN_MATCHER_HPP_ */
