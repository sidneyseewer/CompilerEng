#include "NextUseCalc.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/VarSymbol.h"
#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
constexpr const char *const strReplace(char *str, char c, size_t index) {
  // std::string s{};
  str[index] = c;
  return str;
}

TEST_CASE("NUSimpel") {
  NextUseCalc uut{};
  auto s1 = ConstSymbol::create("4", nullptr);
  auto s2 = VarSymbol::create("a", nullptr, 0);
  std::vector<dac::Entry::ptr> code;
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::SymbolOperand::create(s1),
                                    dac::SymbolOperand::create(s1)));
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::DacOperand::createResult(code[0]),
                                    dac::SymbolOperand::create(s1)));
  code.push_back(dac::Entry::create(dac::OpKind::Add,dac::SymbolOperand::create(s1),
                                    dac::DacOperand::createResult(code[1])
                                    ));
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::SymbolOperand::create(s1),
                                    dac::SymbolOperand::create(s1)));
  for (size_t i = 0; i < code.size(); i++) {
    code[i]->setPosition(i);
  }
  uut.Calc(code.begin(), code.end());

//   auto g = code;
//   std::vector<std::pair<std::string, Symbol::ptr>> st{};
//   st.emplace_back("4", s1);
//   st.emplace_back("a", s2);
//   constexpr auto a = "{:6}: ";
//   constexpr auto b = "{: >6} ";
//   constexpr auto c = "&{: <5} ";

//   std::cout << std::format(a, ' ');
//   for (auto s : st) {
//     std::cout << std::format(b, s.first);
//   }
//   for (auto s : g) {
//     std::cout << std::format(c, s->getPosition());
//   }
//   std::cout << std::endl;
//   for (size_t i = 0; i < g.size(); i++) {
//     auto e = *(g.begin() + i);
//     std::cout << std::format(a, i);
//     for (auto s : st) {
//       dac::Operand::ptr p = dac::SymbolOperand::create(s.second);
//       if (e->hasNextUse(p))
//         std::cout << std::format(b, e->getNextUse(p));
//       else
//         std::cout << std::format(b, '-');
//     }
//     for (auto s : g) {
//       dac::Operand::ptr p = dac::DacOperand::createResult(s);
//       if (e->hasNextUse(p))
//         std::cout << std::format(b, e->getNextUse(p));
//       else
//         std::cout << std::format(b, '-');
//     }
//     std::cout << dac::OpKindToString(e.get()->getKind());
//     std::cout << " " << toString(e->getFirst()) << " "
//               << toString(e->getSecond()) << std::endl;
//   }

  REQUIRE(code[0]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[1])));
//   REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[1])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[0]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[0]->getNextUse(dac::SymbolOperand::create(s1)) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[1]->hasNextUse(dac::DacOperand::createResult(code[1])));
  REQUIRE(code[1]->getNextUse(dac::DacOperand::createResult(code[1])) == 2);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[1]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[1]->getNextUse(dac::SymbolOperand::create(s1)) == 2);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[0])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[1])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[1])) == 1);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[2])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[2])) == 1);
  REQUIRE(code[2]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[2]->getNextUse(dac::SymbolOperand::create(s1)) == 3);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::SymbolOperand::create(s2)));
}

TEST_CASE("NUSimpel2") {
  NextUseCalc uut{};
  auto s1 = ConstSymbol::create("4", nullptr);
  auto s2 = VarSymbol::create("a", nullptr, 0);
  std::vector<dac::Entry::ptr> code;
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::SymbolOperand::create(s1),
                                    dac::SymbolOperand::create(s1)));
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::DacOperand::createResult(code[0]),
                                    dac::SymbolOperand::create(s1)));
  code.push_back(dac::Entry::create(dac::OpKind::Assign,
                                    dac::SymbolOperand::create(s2),
                                    dac::DacOperand::createResult(code[1])));
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::DacOperand::createResult(code[1]),
                                    dac::SymbolOperand::create(s1)));
  for (size_t i = 0; i < code.size(); i++) {
    code[i]->setPosition(i);
  }
  uut.Calc(code.begin(), code.end());

  auto g = code;
  std::vector<std::pair<std::string, Symbol::ptr>> st{};
  st.emplace_back("4", s1);
  st.emplace_back("a", s2);
  prt(g,st);

  REQUIRE(code[0]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[1])));
//   REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[1])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[0]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[0]->getNextUse(dac::SymbolOperand::create(s1)) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[1]->hasNextUse(dac::DacOperand::createResult(code[1])));
  REQUIRE(code[1]->getNextUse(dac::DacOperand::createResult(code[1])) == 2);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[1]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[1]->getNextUse(dac::SymbolOperand::create(s1)) == 3);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[0])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE(code[2]->hasNextUse(dac::DacOperand::createResult(code[1])));
  REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[1])) == 3);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[2])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[2])) == 1);
  REQUIRE(code[2]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[2]->getNextUse(dac::SymbolOperand::create(s1)) == 3);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::SymbolOperand::create(s2)));
}


TEST_CASE("NUSimpel3") {
  NextUseCalc uut{};
  auto s1 = ConstSymbol::create("4", nullptr);
  auto s2 = ConstSymbol::create("2", nullptr);
  auto s3 = ConstSymbol::create("5", nullptr);
  auto s4 = ConstSymbol::create("3", nullptr);
  auto s5 = VarSymbol::create("b", nullptr, 0);
  std::vector<dac::Entry::ptr> code;
  code.push_back(dac::Entry::create(dac::OpKind::Add,
                                    dac::SymbolOperand::create(s3),
                                    dac::SymbolOperand::create(s2)));
  code.push_back(dac::Entry::create(dac::OpKind::Mult,dac::SymbolOperand::create(s4),
                                    dac::DacOperand::createResult(code[0])
                                    ));
  code.push_back(dac::Entry::create(dac::OpKind::Mult,
                                    dac::DacOperand::createResult(code[1]),
                                    dac::SymbolOperand::create(s4)));
  code.push_back(dac::Entry::create(dac::OpKind::Div,
                                    dac::DacOperand::createResult(code[2]),
                                    dac::SymbolOperand::create(s1)));
  code.push_back(dac::Entry::create(dac::OpKind::Sub,
                                    dac::DacOperand::createResult(code[3]),
                                    dac::SymbolOperand::create(s2)));
  code.push_back(dac::Entry::create(dac::OpKind::Assign,
                                    dac::SymbolOperand::create(s5),
                                    dac::DacOperand::createResult(code[4])));
  code.push_back(dac::Entry::create(dac::OpKind::Print,
                                    dac::SymbolOperand::create(s5)));
  for (size_t i = 0; i < code.size(); i++) {
    code[i]->setPosition(i);
  }
  uut.Calc(code.begin(), code.end());

  auto g = code;
  std::vector<std::pair<std::string, Symbol::ptr>> st{};
  st.emplace_back("4", s1);
  st.emplace_back("2", s2);
  st.emplace_back("5", s3);
  st.emplace_back("3", s4);
  st.emplace_back("b", s5);
  prt(g,st);

  REQUIRE(code[0]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[1])));
//   REQUIRE(code[0]->getNextUse(dac::DacOperand::createResult(code[1])) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[0]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[0]->getNextUse(dac::SymbolOperand::create(s1)) == 1);
  REQUIRE_FALSE(code[0]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[0])));
  REQUIRE(code[1]->hasNextUse(dac::DacOperand::createResult(code[1])));
  REQUIRE(code[1]->getNextUse(dac::DacOperand::createResult(code[1])) == 2);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::DacOperand::createResult(code[2])));
  REQUIRE(code[1]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[1]->getNextUse(dac::SymbolOperand::create(s1)) == 3);
  REQUIRE_FALSE(code[1]->hasNextUse(dac::SymbolOperand::create(s2)));


  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[0])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[0])) == 1);
  REQUIRE(code[2]->hasNextUse(dac::DacOperand::createResult(code[1])));
  REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[1])) == 3);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::DacOperand::createResult(code[2])));
//   REQUIRE(code[2]->getNextUse(dac::DacOperand::createResult(code[2])) == 1);
  REQUIRE(code[2]->hasNextUse(dac::SymbolOperand::create(s1)));
  REQUIRE(code[2]->getNextUse(dac::SymbolOperand::create(s1)) == 3);
  REQUIRE_FALSE(code[2]->hasNextUse(dac::SymbolOperand::create(s2)));
}