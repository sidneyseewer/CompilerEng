/**
 * @file DacOperand.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Code Refference Operand
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __DAC_DAC_OPERAND_H__
#define __DAC_DAC_OPERAND_H__

#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class Entry;
using Entry_ptr = std::shared_ptr<Entry>;
/**
 * @brief Code Refference Operand
 * 
 */
class DacOperand : public Operand {
  Entry_ptr mResult = nullptr;
  Entry_ptr mJump = nullptr;
  void x() override {}

public:

  using ptr = std::shared_ptr<DacOperand>;
  /**
   * @brief Get the Result Entry
   * 
   * @return Entry_ptr 
   */
  Entry_ptr getResult();
  /**
   * @brief Get the Jump Entry
   * 
   * @return Entry_ptr 
   */
  Entry_ptr getJump();
  /**
   * @brief get result if exists jump otherwise
   * 
   * @return Entry_ptr 
   */
  Entry_ptr get();
  /**
   * @brief test if Operand is result refference
   * 
   * @return true if Operand has result refference
   * @return false otherwise
   */
  bool isResult();
  /**
   * @brief test if Operand is Jump refference
   * 
   * @return true if Operand has Jump refference
   * @return false otherwise
   */
  bool isJump();
  enum Type { Result, Jump };
  /**
   * @brief Construct a new Dac Operand object
   * 
   * @param entr Entry to refference to
   * @param tp type of the refference
   */
  DacOperand(Entry_ptr const& entr, Type const&tp);
  /**
   * @brief Create a DacOperand with Result refference
   * 
   * @param e Entry to refference to
   * @return DacOperand::ptr 
   */
  static DacOperand::ptr createResult(Entry_ptr const &e) {
    return std::make_shared<DacOperand>(e, Result);
  };
  /**
   * @brief Create a DacOperand with Jump refference
   * 
   * @param e Entry to refference to
   * @return DacOperand::ptr 
   */
  static DacOperand::ptr createJump(Entry_ptr const &e) {
    return std::make_shared<DacOperand>(e, Jump);
  };
  /**
   * @brief test if Operand is DacOperand
   * 
   * @param o Operand to test
   * @return true 
   * @return false 
   */
  static bool is(Operand::ptr const &o) {
    if (o != nullptr)
      return dac::extract<DacOperand>(o) != nullptr;
    return false;
  }
};
} // namespace dac

#endif //!__DAC_DAC_OPERAND_H__