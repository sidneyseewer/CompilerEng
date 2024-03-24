/**
 * @file Generator.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Code Generation Algorithmus
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __DAC_GENERATOR_H__
#define __DAC_GENERATOR_H__

#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <cstddef>
#include <vector>
namespace dac {
/**
 * @brief Code Generation Algorithmus
 * 
 */
class Generator {
public:
  using codeContainer_type = std::vector<Entry::ptr>;
  /**
   * @brief add entry with first operand
   * 
   * @param kind 
   * @param first 
   */
  void add(OpKind const &kind, Operand::ptr const &first);
  /**
   * @brief add Jump entry
   * 
   * @param kind 
   * @param index 
   */
  void add(OpKind const &kind, size_t const &index);
  /**
   * @brief add entry at level C
   * 
   * @param kind 
   */
  void add(OpKind const &kind);
  /**
   * @brief add entry at level B
   * 
   * @param kind 
   */
  void addt(OpKind const &kind);
  /**
   * @brief add entry at level A
   * 
   * @param kind 
   */
  void addf(OpKind const &kind);
  /**
   * @brief add second operand of last entry
   * 
   * @param op 
   */
  void add(Operand::ptr const &op);
  /**
   * @brief push Parentethies
   * 
   */
  void pushPr();
  /**
   * @brief pop parentethies
   * 
   */
  void popPr();
  /**
   * @brief create new flow Context
   * inside if,while
   */
  void pushContext();
  /**
   * @brief finish current flow context
   * after if,while
   */
  void popContext();
  /**
   * @brief set jump index of context
   * 
   */
  void ContextSetIndex();
  /**
   * @brief get jump index of context
   * 
   * @return size_t 
   */
  size_t ContextGetIndex() const;
  /**
   * @brief set jump refference of context
   * 
   */
  void ContextSetRef();

  void ContextRef(int const &offset = 0);
  /**
   * @brief finish a statement and write it to code
   * 
   */
  void endStmt();
  /**
   * @brief Get the generated code
   * 
   * @return codeContainer_type 
   */
  codeContainer_type getCode();
  /**
  @brief sets the position member of each entry to the index in the code array
  */
  void updateIndex();
  /**
   * @brief Construct a new Generator object
   * 
   */
  Generator();
  codeContainer_type::const_iterator cend() const;
  codeContainer_type::const_iterator cbegin() const;
  codeContainer_type::iterator begin();
  codeContainer_type::iterator end();
  size_t size() const;
  Entry::ptr operator[](size_t const &index);
  /**
   * @brief add entry to code
   * 
   * @param a 
   */
  void add(Entry::ptr const &a);
  /**
   * @brief turn jump refferences to relative line numbers
   * 
   */
  void updateJumpRefs();

private:
  struct FlowContext {
    Entry::ptr ref;
    size_t index;
  };
  struct StatementContext {
    Entry::ptr root;
    Entry::ptr A;
    Entry::ptr B;
    Entry::ptr C;
  };
  struct JumpRef {
    Entry::ptr entry;
    size_t destination;
  };

  codeContainer_type code{};
  std::vector<FlowContext> flowContext{};
  std::vector<StatementContext> statementContext{};
  std::vector<JumpRef> jumpRefs{};
};
} // namespace dac
#endif //!__DAC_GENERATOR_H__