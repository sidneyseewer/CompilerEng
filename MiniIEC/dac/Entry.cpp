/**
 * @file Entry.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 3-Address Code Entry Implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Entry.h"

using namespace dac;

void Entry::setPosition(size_t const &p) { pos = p; }
size_t Entry::getPosition() const { return pos; }
Entry::Entry(OpKind const &k, Operand::ptr const &first,
             Operand::ptr const &second)
    : mOpKind(k), mFirst(first), mSec(second) {}
Entry::Entry(OpKind const &k, Operand::ptr const &first)
    : mOpKind(k), mFirst(first), mSec(nullptr) {}
Entry::Entry(OpKind const &k) : mOpKind(k), mFirst(nullptr), mSec(nullptr) {}

void Entry::setSecond(Operand::ptr const &op) { mSec = op; };
void Entry::setFirst(Operand::ptr const &op) { mFirst = op; };
Operand::ptr &Entry::getFirst() { return mFirst; }
Operand::ptr &Entry::getSecond() { return mSec; }
OpKind Entry::getKind() const { return mOpKind; }
bool Entry::hasNextUse(nextUse_keytype ptr) const {
  bool ret = false;
  for (auto u : nextUses) {
    if (Compare_operand_pointer<std::equal_to<void *>>(u.first, ptr))
      ret = true;
  }
  return ret;
}
void Entry::addnextUsed(Entry::nextUse_keytype const &sym,
                        Entry::nextUse_valuetype const &t) {
  // nextUses[sym]=t;
  for (auto u : nextUses) {
    if (Compare_operand_pointer<std::equal_to<void *>>(u.first, sym))
      return;
  }
  nextUses.emplace_back(sym, t);
}
Entry::nextUse_valuetype
Entry::getNextUse(Entry::nextUse_keytype const &ptr) const {
  for (auto u : nextUses) {
    if (Compare_operand_pointer<std::equal_to<void *>>(u.first, ptr))
      return u.second;
  }
  throw new std::out_of_range(" index ou tof range");
}
