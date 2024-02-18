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