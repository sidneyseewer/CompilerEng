/**
 * @file SymbolFactory.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Symbol factory Implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "SymbolFactory.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

using namespace std;

SymbolFactory::SymbolFactory() {
  auto x = TypeSymbol::create("integer", BaseType::create(INT, 4));
  mTypeSymbol = x;
}
Symbol::ptr SymbolFactory::CreateConst(string const &name) {

  return ConstSymbol::create(name, mTypeSymbol->getType());
}
Symbol::ptr SymbolFactory::CreateType(string const &name) {
  if (name != "Integer") {
    // throw "unknown type";
    // TODO:  error message "-- line 4 col 8: "Integer" expected"
  }
  return mTypeSymbol;
}
Symbol::ptr SymbolFactory::CreateVar(string const &name) {
  std::size_t offset = mOffset;
  auto a = mTypeSymbol->getType();
  auto b = a->getSize();
  mOffset += b;
  return VarSymbol::create(name, mTypeSymbol->getType(), offset);
}