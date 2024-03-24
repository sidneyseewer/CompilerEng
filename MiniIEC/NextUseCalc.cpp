/**
 * @file NextUseCalc.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "NextUseCalc.h"



void NextUseCalc::addOP(dac::Operand::ptr const &ps, size_t const &i) {

  auto a = extract<dac::SymbolOperand>(ps);
  dac::DacOperand *b = extract<dac::DacOperand>(ps);
  if (a != nullptr || (b != nullptr && b->isResult()))
    lu[ps] = i;
}
