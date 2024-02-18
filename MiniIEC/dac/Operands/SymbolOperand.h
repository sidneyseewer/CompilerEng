#ifndef __DAC_SYMBOL_OPERAND_H__
#define __DAC_SYMBOL_OPERAND_H__

#include "Symbols/Symbol.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class SymbolOperand : public Operand {
  Symbol::ptr mSymbol;
  void x() override{};

public:
  using ptr = std::shared_ptr<SymbolOperand>;
  Symbol::ptr get() const;
  SymbolOperand(Symbol::ptr const &s);
  static ptr create(Symbol::ptr const &s) {
    return std::make_shared<SymbolOperand>(s);
  }
};
} // namespace dac

#endif //!__DAC_SYMBOL_OPERAND_H__