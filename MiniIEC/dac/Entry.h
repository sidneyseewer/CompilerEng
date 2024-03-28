/**
 * @file Entry.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 3-Address Code Entry
 * @version 0.1
 * @date 2024-03-24
 *
 * @copyright Copyright (c) 2024
 *
 */
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
#include "Object.h"
namespace dac {
/**
 * @brief 3-Address Code Entry
 *
 */
class Entry :Object{
private:
  OpKind mOpKind;
  Operand::ptr mFirst;
  Operand::ptr mSec;
  size_t pos;

public:
  bool isJumpDestination = false;
  /**
   * @brief Set the Position the instruction is in the code
   *
   * @param p Position
   */
  void setPosition(size_t const &p);
  /**
   * @brief Get the Position the instruction is in the code
   *
   * @return size_t
   */
  size_t getPosition() const;
  /**
   * @brief Construct a new Entry object
   *
   * @param k Operand kind
   * @param first first Operand
   * @param second Second Operand
   */
  Entry(OpKind const &k, Operand::ptr const &first, Operand::ptr const &second);
  /**
   * @brief Construct a new Entry with 1 Operand
   *
   * @param k Operand kind
   * @param first first Operamd
   */
  Entry(OpKind const &k, Operand::ptr const &first);
  /**
   * @brief Construct a new Entry with no operand
   *
   * @param k Operand kind
   */
  Entry(OpKind const &k);
  using ptr = std::shared_ptr<Entry>;
  /**
   * @brief Set the Second Operand
   *
   * @param op
   */
  void setSecond(Operand::ptr const &op);
  /**
   * @brief Set the First Operand
   *
   * @param op
   */
  void setFirst(Operand::ptr const &op);
  /**
   * @brief Get the First Operand
   *
   * @return Operand::ptr&
   */
  Operand::ptr &getFirst();
  /**
   * @brief Get the Second Opernad
   *
   * @return Operand::ptr&
   */
  Operand::ptr &getSecond();
  /**
   * @brief Get the Operand Kind
   *
   * @return OpKind
   */
  OpKind getKind() const;
  /**
   * @brief create new Entry with 2 Operands
   *
   * @param k Kind
   * @param first first Operand
   * @param second Second Operand
   * @return Entry::ptr
   */
  static Entry::ptr create(OpKind const &k, Operand::ptr const &first,
                           Operand::ptr const &second) {
    return std::make_shared<Entry>(k, first, second);
  }
  /**
   * @brief create new Entry with 1 Operands
   *
   * @param k Kind
   * @param first first Operand
   * @return Entry::ptr
   */
  static Entry::ptr create(OpKind const &k, Operand::ptr const &first) {
    return std::make_shared<Entry>(k, first);
  }
  /**
   * @brief create new Entry with no Operands
   *
   * @param k Kind
   * @return Entry::ptr
   */
  static Entry::ptr create(OpKind const &k) {
    return std::make_shared<Entry>(k);
  }
  // next use line or 0 for no use
  using nextUse_valuetype = size_t;
  using nextUse_keytype = Operand::ptr;
  /**
   * @brief test if Operand has following uses
   * @note next usage needs to be manualy generated
   * @param ptr
   * @return true
   * @return false
   */
  bool hasNextUse(nextUse_keytype ptr) const;
  /**
   * @brief add next usage for Operand
   * @param sym Operand to use
   * @param t Line of next usage
   */
  void addnextUsed(nextUse_keytype const &sym, nextUse_valuetype const &t);
  /**
   * @brief Get the line of next usage
   *
   * @param ptr
   * @return nextUse_valuetype
   */
  nextUse_valuetype getNextUse(nextUse_keytype const &ptr) const;

private:
  std::vector<std::pair<nextUse_keytype, nextUse_valuetype>> nextUses{};
};
} // namespace dac

#endif //!__DAC_ENTRY_H__