/**
 * This file copyright (c) 2011-2015, Quickstep Technologies LLC.
 * Copyright (c) 2015, Pivotal Software, Inc.
 * All rights reserved.
 * See file CREDITS.txt for details.
 **/

#ifndef QUICKSTEP_PARSER_PARSE_TABLE_REFERENCE_HPP_
#define QUICKSTEP_PARSER_PARSE_TABLE_REFERENCE_HPP_

#include <memory>
#include <string>
#include <vector>

#include "parser/ParseString.hpp"
#include "parser/ParseTreeNode.hpp"
#include "utility/Macros.hpp"
#include "utility/PtrList.hpp"

namespace quickstep {

/** \addtogroup Parser
 *  @{
 */

/**
 * @brief A table signature for a derived or base table that represents
 *        the table alias (correlation name) and derived
 *        column alias list.
 */
class ParseTableReferenceSignature : public ParseTreeNode {
 public:
  /**
   * @brief Constructor. Takes ownership of all pointers.
   *
   * @param line_number The line number of the first token of this node in the SQL statement.
   * @param column_number The column number of the first token of this node in the SQL statement.
   * @param table_alias The table alias.
   * @param column_aliases The column names for the table.
   */
  ParseTableReferenceSignature(const int line_number,
                               const int column_number,
                               ParseString *table_alias,
                               PtrList<ParseString> *column_aliases = nullptr)
      : ParseTreeNode(line_number, column_number),
        table_alias_(table_alias),
        column_aliases_(column_aliases) {
  }

  /**
   * @brief Destructor.
   */
  ~ParseTableReferenceSignature() override {}

  /**
   * @return The table alias.
   */
  const ParseString* table_alias() const { return table_alias_.get(); }

  /**
   * @return The column aliases.
   */
  const PtrList<ParseString>* column_aliases() const { return column_aliases_.get(); }

  std::string getName() const override { return "TableSignature"; }

 protected:
  void getFieldStringItems(
      std::vector<std::string> *inline_field_names,
      std::vector<std::string> *inline_field_values,
      std::vector<std::string> *non_container_child_field_names,
      std::vector<const ParseTreeNode*> *non_container_child_fields,
      std::vector<std::string> *container_child_field_names,
      std::vector<std::vector<const ParseTreeNode*>> *container_child_fields) const override;

 private:
  std::unique_ptr<ParseString> table_alias_;
  std::unique_ptr<PtrList<ParseString>> column_aliases_;

  DISALLOW_COPY_AND_ASSIGN(ParseTableReferenceSignature);
};

/**
 * @brief Base class for a FROM-list table item, which may be a subquery expression or a simple table reference.
 */
class ParseTableReference : public ParseTreeNode {
 public:
  enum TableReferenceType {
    kSimpleTableReference,
    kSubqueryTableReference
  };

  /**
   * @brief Destructor.
   */
  ~ParseTableReference() override {}

  /**
   * @return The TableReferenceType of this table reference.
   */
  virtual TableReferenceType getTableReferenceType() const = 0;

  /**
   * @brief Sets the table reference signature which gives the table name and table column names that can be used
   *        to reference the table.
   * @note Takes ownership of \p table_reference_signature.
   *
   * @param table_reference_signature The table reference signature.
   */
  void set_table_reference_signature(ParseTableReferenceSignature* table_reference_signature) {
    table_reference_signature_.reset(table_reference_signature);
  }

  /**
   * @return The table reference signature.
   */
  const ParseTableReferenceSignature* table_reference_signature() const {
    return table_reference_signature_.get();
  }

 protected:
  ParseTableReference(const int line_number, const int column_number)
      : ParseTreeNode(line_number, column_number) {
  }

  void getFieldStringItems(
      std::vector<std::string> *inline_field_names,
      std::vector<std::string> *inline_field_values,
      std::vector<std::string> *non_container_child_field_names,
      std::vector<const ParseTreeNode*> *non_container_child_fields,
      std::vector<std::string> *container_child_field_names,
      std::vector<std::vector<const ParseTreeNode*>> *container_child_fields) const override;

 private:
  std::unique_ptr<ParseTableReferenceSignature> table_reference_signature_;

  DISALLOW_COPY_AND_ASSIGN(ParseTableReference);
};

/** @} */

}  // namespace quickstep

#endif  // QUICKSTEP_PARSER_PARSE_TABLE_REFERENCE_HPP_
