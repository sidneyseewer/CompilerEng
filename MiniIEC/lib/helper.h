/**
 * @file helper.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief helper functions
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HELPER_H__
#define __HELPER_H__

#include "dac/Operands/DacOperand.h"
// #include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <algorithm>
#include <cstddef>
#include <format>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <codecvt>
#include <string>
#include "SymbolTable.h"

std::wstring toString(dac::Operand::ptr const& p);
/**
 * @brief compare 2 Operand Pointers
 * 
 * @tparam UnaryPredicate 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
template <class UnaryPredicate>
bool Compare_operand_pointer(dac::Operand::ptr const &a,
                             dac::Operand::ptr const &b) {
  UnaryPredicate p{};
  auto a1 = dac::extract<dac::SymbolOperand>(a);
  auto b1 = dac::extract<dac::SymbolOperand>(b);
  auto a2 = dac::extract<dac::DacOperand>(a);
  auto b2 = dac::extract<dac::DacOperand>(b);
  if (a1 != nullptr && b1 != nullptr) {
    auto pa = a1->get().get();
    auto pb = b1->get().get();
    return p(a1->get().get(), b1->get().get());
  }
  if (a2 != nullptr && b2 != nullptr) {
    auto pa = a2->get().get();
    auto pb = b2->get().get();
    return p(a2->get().get(), b2->get().get());
  }

  auto pa = a.get();
  auto pb = b.get();
  if (p(a.get(), b.get()))
    return true;
  return false;
}
template <class UP> struct OperandPointer {
  constexpr bool operator()(dac::Operand::ptr const &a,
                            dac::Operand::ptr const &b) const {
    return Compare_operand_pointer<UP>(a, b);
  }
};

struct Format {
  const char *const a;
  const char *const b;
  const char *const c;
};
constexpr Format formats[] = {{"{:2}: ", "{: >2} ", "&{ <1}"},
                              {"{:3}: ", "{: >3} ", "&{ <2}"},
                              {"{:4}: ", "{: >4} ", "&{ <3}"},
                              {"{:5}: ", "{: >5} ", "&{ <4}"},
                              {"{:6}: ", "{: >6} ", "&{ <5}"}};
constexpr size_t space=4;
void ptra(std::wostream &ost,auto s){ost<<std::setw(space)<<s<<L":";}
void ptrb(std::wostream &ost,auto s){ost<<std::setw(space)<<s;}
void ptrc(std::wostream &ost,auto s){ost<<'&'<<std::setw(space-1)<<std::left<<s;}

template <class T>
void prt(T &g, SymbolTable &st, std::wostream &ost = std::wcout) {

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  // ost << std::format(a, ' ');
  ptra(ost,L' ');
  for (auto s : st) {
    ptrb(ost,converter.from_bytes(s.first));
  }
  for (auto s : g) {
    // ost << std::format(c, s->getPosition());
    ptrc(ost,s->getPosition());
  }
  ost << std::endl;
  for (size_t i = 0; i < g.size(); i++) {
    auto e = *(g.begin() + i);
    // ost << std::format(a, e->getPosition());
    ptra(ost,e->getPosition());
    for (auto s : st) {
      dac::Operand::ptr p = dac::SymbolOperand::create(s.second);
      if (e->hasNextUse(p))
        // ost << std::format(b, e->getNextUse(p));
        ptrb(ost,e->getNextUse(p));
      else
        // ost << std::format(b, L'-');
        ptrb(ost,L'-');
    }
    for (auto s : g) {
      dac::Operand::ptr p = dac::DacOperand::createResult(s);
      if (e->hasNextUse(p))
        // ost << std::format(b, e->getNextUse(p));
        ptrb(ost,e->getNextUse(p));
      else
        // ost << std::format(b, '-');
        ptrb(ost,L'-');
    }
    ost << (e.get()->isJumpDestination ? L'x' : L' ')
              << dac::OpKindToString(e.get()->getKind());
    ost << " " << toString(e->getFirst()) << " "
              << toString(e->getSecond()) << std::endl;
  }
}
#endif //!__HELPER_H__