#ifndef __DAC_DAC_OPERAND_H__
#define __DAC_DAC_OPERAND_H__

#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class Entry;
using Entry_ptr = std::shared_ptr<Entry>;

class DacOperand : public Operand {
  Entry_ptr mResult = nullptr;
  Entry_ptr mJump = nullptr;

public:
  using ptr = std::shared_ptr<DacOperand>;
  void x() override {}
  Entry_ptr getResult();
  Entry_ptr getJump();
  Entry_ptr get();
  bool isResult();
  bool isJump();
  enum Type { Result, Jump };
  DacOperand(Entry_ptr const& entr, Type const&tmp);
  // using ptr = std::shared_ptr<DacOperand>;
  static DacOperand::ptr createResult(Entry_ptr const &e) {
    return std::make_shared<DacOperand>(e, Result);
  };
  static DacOperand::ptr createJump(Entry_ptr const &e) {
    return std::make_shared<DacOperand>(e, Jump);
  };
  static bool is(Operand::ptr const &o) {
    if (o != nullptr)
      return dac::extract<DacOperand>(o) != nullptr;
    return false;
  }
};
} // namespace dac

#endif //!__DAC_DAC_OPERAND_H__