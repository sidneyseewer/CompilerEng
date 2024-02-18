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
  SymbolFactory();
  Symbol::ptr CreateVar(std::string const &name);
  Symbol::ptr CreateConst(std::string const &name);
  Symbol::ptr CreateType(std::string const &name);
};

#endif //!__SYMBOL_FACTORY_H__
