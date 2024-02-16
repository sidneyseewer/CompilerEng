#ifndef __DAC_ENTRY_H__
#define __DAC_ENTRY_H__

#include "Symbols/Symbol.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include "lib/helper.h"
#include <map>
#include <memory>
#include <utility>
#include <variant>
namespace dac {
class Entry {
private:
  OpKind mOpKind;
  Operand::ptr mFirst;
  Operand::ptr mSec;
  size_t pos;
public:
  void setPosition(size_t p){pos=p;}
  size_t getPosition(){return pos;}
  Entry(OpKind k, Operand::ptr first, Operand::ptr second)
      : mOpKind(k), mFirst(first), mSec(second) {}
  Entry(OpKind k, Operand::ptr first)
      : mOpKind(k), mFirst(first), mSec(nullptr) {}
  Entry(OpKind k) : mOpKind(k), mFirst(nullptr), mSec(nullptr) {}
  using ptr = std::shared_ptr<Entry>;
  void setSecond(Operand::ptr op) { mSec = op; };
  void setFirst(Operand::ptr op) { mFirst = op; };
  Operand::ptr &getFirst() { return mFirst; }
  Operand::ptr &getSecond() { return mSec; }
  OpKind getKind() { return mOpKind; }
  static Entry::ptr create(OpKind k, Operand::ptr first, Operand::ptr second) {
    return std::make_shared<Entry>(k, first, second);
  }
  static Entry::ptr create(OpKind k, Operand::ptr first) {
    return std::make_shared<Entry>(k, first);
  }
  static Entry::ptr create(OpKind k) { return std::make_shared<Entry>(k); }
    //next use line or 0 for no use
  using nextUse_valuetype = size_t;
  using nextUse_keytype = Operand::ptr;
  bool hasNextUse(nextUse_keytype ptr){
    return nextUses.contains(ptr);
  }
  void addnextUsed(nextUse_keytype sym,nextUse_valuetype t)
  {
    nextUses[sym]=t;
  }
  nextUse_valuetype getNextUse(nextUse_keytype ptr) {
       return nextUses.at(ptr);
    }

private:
  std::map<nextUse_keytype, nextUse_valuetype,OperandPointer<std::less<void*>>> nextUses{};
};
} // namespace dac

#endif //!__DAC_ENTRY_H__