#ifndef __DAC_GENERATOR_H__
#define __DAC_GENERATOR_H__

#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <cstddef>
#include <vector>
namespace dac {

class Generator {
public:
  using codeContainer_type = std::vector<Entry::ptr>;
  void add(OpKind const &index, Operand::ptr const &first);
  void add(OpKind const &kind, size_t const &index);
  void add(OpKind const &kind);
  void addt(OpKind const &kind);
  void addf(OpKind const &kind);
  void add(Operand::ptr const &op);
  void pushPr();
  void popPr();
  void pushContext();
  void popContext();
  void ContextSetIndex();
  size_t ContextGetIndex() const;
  void ContextSetRef();
  void ContextRef(int const &offset = 0);
  void endStmt();
  codeContainer_type getCode();
  /**
  sets the position member of each entry to the index in the code array
  */
  void updateIndex();
  Generator();
  codeContainer_type::const_iterator cend() const;
  codeContainer_type::const_iterator cbegin() const;
  codeContainer_type::iterator begin();
  codeContainer_type::iterator end();
  size_t size() const;
  void add(Entry::ptr const &a);
  Entry::ptr operator[](size_t const &index);
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