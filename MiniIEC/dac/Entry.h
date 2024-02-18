#ifndef __DAC_ENTRY_H__
#define __DAC_ENTRY_H__

#include "Symbols/Symbol.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include "lib/helper.h"
#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>
#include <variant>
#include <vector>
namespace dac {
class Entry {
private:
  OpKind mOpKind;
  Operand::ptr mFirst;
  Operand::ptr mSec;
  size_t pos;

public:
  bool isJumpDestination = false;
  void setPosition(size_t const &p);
  size_t getPosition() const;
  Entry(OpKind const &k, Operand::ptr const &first, Operand::ptr const &second);
  Entry(OpKind const &k, Operand::ptr const &first);
  Entry(OpKind const &k);
  using ptr = std::shared_ptr<Entry>;
  void setSecond(Operand::ptr const &op);
  void setFirst(Operand::ptr const &op);
  Operand::ptr &getFirst();
  Operand::ptr &getSecond();
  OpKind getKind() const;
  static Entry::ptr create(OpKind const &k, Operand::ptr const &first,
                           Operand::ptr const &second) {
    return std::make_shared<Entry>(k, first, second);
  }
  static Entry::ptr create(OpKind const &k, Operand::ptr const &first) {
    return std::make_shared<Entry>(k, first);
  }
  static Entry::ptr create(OpKind const &k) {
    return std::make_shared<Entry>(k);
  }
  // next use line or 0 for no use
  using nextUse_valuetype = size_t;
  using nextUse_keytype = Operand::ptr;
  bool hasNextUse(nextUse_keytype ptr) const;
  void addnextUsed(nextUse_keytype const &sym, nextUse_valuetype const &t);
  nextUse_valuetype getNextUse(nextUse_keytype const &ptr) const;

private:
  //  std::map<nextUse_keytype,
  //  nextUse_valuetype,OperandPointer<std::less<void*>>>
  std::vector<std::pair<nextUse_keytype, nextUse_valuetype>> nextUses{};
};
} // namespace dac

#endif //!__DAC_ENTRY_H__