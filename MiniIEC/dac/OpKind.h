/**
 * @file OpKind.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Suppored Operation and convertion to string
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __DAC_OP_KIND_H__
#define __DAC_OP_KIND_H__

#include <string>
namespace dac {
  /**
   * @brief Contains al Operations known by the 3AC
   * 
   */
enum OpKind {
  Add,
  Sub,
  Mult,
  Div,
  IsEq,
  IsLeq,
  IsGtq,
  IsNotEq,
  IsLess,
  IsGreater,
  Assign,
  Jump,
  IfFalse,
  Print,
  Exit
};
/**
 * @brief Turn OpKind to String for printing
 * 
 * @param opk 
 * @return std::string 
 */
static std::string OpKindToString(OpKind const &opk) {
  switch (opk) {
  case Add:
    return "Add";
  case Sub:
    return "Sub";
  case Mult:
    return "Mult";
  case Div:
    return "Div";
  case IsEq:
    return "IsEq";
  case IsLeq:
    return "IsLeq";
  case IsGtq:
    return "IsGtq";
  case IsNotEq:
    return "IsNotEq";
  case IsLess:
    return "IsLess";
  case IsGreater:
    return "IsGreater";
  case Assign:
    return "Assign";
  case Jump:
    return "Jump";
  case IfFalse:
    return "IfFalse";
  case Print:
    return "Print";
  case Exit:
    return "Exit";
  }
  return "-";
}
} // namespace dac

#endif //!__DAC_OP_KIND_H__