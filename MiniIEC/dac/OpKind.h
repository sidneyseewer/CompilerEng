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
static std::wstring OpKindToString(OpKind const &opk) {
  switch (opk) {
  case Add:
    return L"Add";
  case Sub:
    return L"Sub";
  case Mult:
    return L"Mult";
  case Div:
    return L"Div";
  case IsEq:
    return L"IsEq";
  case IsLeq:
    return L"IsLeq";
  case IsGtq:
    return L"IsGtq";
  case IsNotEq:
    return L"IsNotEq";
  case IsLess:
    return L"IsLess";
  case IsGreater:
    return L"IsGreater";
  case Assign:
    return L"Assign";
  case Jump:
    return L"Jump";
  case IfFalse:
    return L"IfFalse";
  case Print:
    return L"Print";
  case Exit:
    return L"Exit";
  }
  return L"-";
}
} // namespace dac

#endif //!__DAC_OP_KIND_H__