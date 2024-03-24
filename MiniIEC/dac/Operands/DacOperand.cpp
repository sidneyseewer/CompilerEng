/**
 * @file DacOperand.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Code Refference Operand Implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "DacOperand.h"
using namespace dac;

Entry_ptr DacOperand::get() { return mResult == nullptr ? mJump : mResult; }
Entry_ptr DacOperand::getResult() { return mResult; }
Entry_ptr DacOperand::getJump() { return mJump; }
bool DacOperand::isResult() { return mResult != nullptr; }
bool DacOperand::isJump() { return mJump != nullptr; }

DacOperand::DacOperand(Entry_ptr const& entr, DacOperand::Type const&tmp)
    : mJump(nullptr), mResult(nullptr) {
  switch (tmp) {
  case Result:
    mResult = entr;
    break;
  case Jump:
    mJump = entr;
    break;
  default:
    throw "enum out of range";
  }
}