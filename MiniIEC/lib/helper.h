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
#include <sstream>

std::string toString(dac::Operand::ptr const& p);

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

template <class T, class F>
void prt(T &g, F &st, std::ostream &cout = std::cout) {
  constexpr auto a = "{:3}: ";
  constexpr auto b = "{: >3} ";
  constexpr auto c = "&{: <2} ";

  std::cout << std::format(a, ' ');
  for (auto s : st) {
    std::cout << std::format(b, s.first);
  }
  for (auto s : g) {
    std::cout << std::format(c, s->getPosition());
  }
  std::cout << std::endl;
  for (size_t i = 0; i < g.size(); i++) {
    auto e = *(g.begin() + i);
    std::cout << std::format(a, e->getPosition());
    for (auto s : st) {
      dac::Operand::ptr p = dac::SymbolOperand::create(s.second);
      if (e->hasNextUse(p))
        std::cout << std::format(b, e->getNextUse(p));
      else
        std::cout << std::format(b, '-');
    }
    for (auto s : g) {
      dac::Operand::ptr p = dac::DacOperand::createResult(s);
      if (e->hasNextUse(p))
        std::cout << std::format(b, e->getNextUse(p));
      else
        std::cout << std::format(b, '-');
    }
    std::cout << (e.get()->isJumpDestination ? 'x' : ' ')
              << dac::OpKindToString(e.get()->getKind());
    std::cout << " " << toString(e->getFirst()) << " "
              << toString(e->getSecond()) << std::endl;
  }
}
#endif //!__HELPER_H__