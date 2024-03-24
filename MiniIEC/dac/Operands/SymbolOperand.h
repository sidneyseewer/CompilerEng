/**
 * @file SymbolOperand.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Symbol Refference Operand
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __DAC_SYMBOL_OPERAND_H__
#define __DAC_SYMBOL_OPERAND_H__

#include "Symbols/Symbol.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
  /**
   * @brief Symbol Refference Operand
   * 
   */
class SymbolOperand : public Operand {
  Symbol::ptr mSymbol;
  void x() override{};

public:
  using ptr = std::shared_ptr<SymbolOperand>;
  /**
   * @brief get Sumbol refference
   * 
   * @return Symbol::ptr 
   */
  Symbol::ptr get() const;
  /**
   * @brief Construct a new Symbol Operand
   * 
   * @param s Symbol to reffere to
   */
  SymbolOperand(Symbol::ptr const &s);
  /**
   * @brief create a new SymbolOperand
   * 
   * @param s Symbol to reffere to
   * @return ptr 
   */
  static ptr create(Symbol::ptr const &s) {
    return std::make_shared<SymbolOperand>(s);
  }
};
} // namespace dac

#endif //!__DAC_SYMBOL_OPERAND_H__