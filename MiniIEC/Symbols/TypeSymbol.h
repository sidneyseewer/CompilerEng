#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/Type.h"
#include <tuple>
class TypeSymbol : public Symbol {

public:
  // using ptr = std::shared_ptr<TypeSymbol>;
  static TypeSymbol::ptr create(std::string name, Type::ptr type) {
    return std::make_shared<TypeSymbol>(name, type);
  }
  TypeSymbol(std::string name, Type::ptr t) : Symbol(name, t) {}
};

#endif //!__TYPE_SYMBOL_H_