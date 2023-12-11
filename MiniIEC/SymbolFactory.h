#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include "lib/Singelton.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

class SymbolFactory : public Singelton<SymbolFactory> {
  friend class Singelton<SymbolFactory>;
  TypeSymbol::ptr mTypeSymbol;
  size_t mOffset = 0;

public:
  SymbolFactory() {
    auto x= TypeSymbol::create("integer", BaseType::create(INT, 4));
    mTypeSymbol=x;
  }
  Symbol::ptr CreateVar(std::string name);
  Symbol::ptr CreateConst(std::string name);
  Symbol::ptr CreateType(std::string name);
};

#endif //!__SYMBOL_FACTORY_H__
