/**
 * @file NextUseCalc.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief calculation of next use
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __NEXT_USE_CALC_H__
#define __NEXT_USE_CALC_H__

#include "Symbols/Symbol.h"
#include "dac/Entry.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include "lib/helper.h"
#include <cstddef>
#include <map>
#include <optional>
#include <sys/types.h>
#include <vector>

/**
 * @brief calculation of next use
 * 
 */
class NextUseCalc {
  using NextUsage_container = std::map<dac::Operand::ptr, std::optional<size_t>,
                                       OperandPointer<std::less<void *>>>;
  NextUsage_container lu{};
  std::map<size_t, bool> usedJumpes;
  void addOP(dac::Operand::ptr const &ps, size_t const &i);

public:
/**
 * @brief start calculation
 * 
 * @tparam Itr 
 * @param begin 
 * @param end 
 */
  template <class Itr> void Calc(Itr const &begin, Itr const &end) {

    constexpr auto set = NextUsage_container::mapped_type{};
    for (int i = end - begin - 1; i >= 0; i--) {
      dac::Entry::ptr e = *(begin + i);
      dac::OpKind op = e->getKind();
      // add next usages to current entry
      for (auto s : lu) {
        if (s.second.has_value())
          e->addnextUsed(s.first, s.second.value());
      }
      // assignemnts
      switch (op) {

      case dac::Add:
      case dac::Sub:
      case dac::Mult:
      case dac::Div:
        // instructions with result stored in register
        lu[dac::DacOperand::createResult(e)] = set;
        break;
      case dac::Assign:
        // instructions with result sored im memory

        lu[e->getFirst()] = set;
        break;
      case dac::IsEq:
      case dac::IsLeq:
      case dac::IsGtq:
      case dac::IsNotEq:
      case dac::IsLess:
      case dac::IsGreater:
      case dac::Jump:
      case dac::IfFalse:
      case dac::Print:
      case dac::Exit:
        break;
      }
      // usages (operands)
      switch (op) {

      case dac::Add:
      case dac::Sub:
      case dac::Mult:
      case dac::Div:

        addOP(e->getFirst(), i);
      case dac::Print:
      case dac::Assign:
        addOP(e->getSecond(), i);
        break;
      case dac::IsEq:
      case dac::IsLeq:
      case dac::IsGtq:
      case dac::IsNotEq:
      case dac::IsLess:
      case dac::IsGreater:
      case dac::Jump:
      case dac::IfFalse:
      case dac::Exit:
        break;
      }
    }
  }
};

#endif //!__NEXT_USE_CALC_H__