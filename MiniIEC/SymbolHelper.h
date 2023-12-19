#ifndef __SYMBOL_HELPER_H__

#define __SYMBOL_HELPER_H__

#include "SymbolFactory.h"
#include "SymbolTable.h"
#include "Symbols/Symbol.h"
class SH {
    public:
  static Symbol::ptr addConstSymbol(std::string name) {
    auto x = SymbolTable::GetInstance().Find(name);
    if (x == nullptr) {
        x=SymbolFactory::GetInstance().CreateConst(name);
        SymbolTable::GetInstance().Add(x);
    }
    return x;
  }
  static Symbol::ptr addVarSymbol(std::string name) {
    auto x = SymbolTable::GetInstance().Find(name);
    if (x == nullptr) {
        x=SymbolFactory::GetInstance().CreateVar(name);
        SymbolTable::GetInstance().Add(x);
    }
    return x;
  }
  static Symbol::ptr addTypeSymbol(std::string name) {
    auto x = SymbolTable::GetInstance().Find(name);
    if (x == nullptr) {
        x=SymbolFactory::GetInstance().CreateType(name);
        SymbolTable::GetInstance().Add(x);
    }
    return x;
  }
};

#endif //!__SYMBOL_HELPER_H__