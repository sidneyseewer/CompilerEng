#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/Type.h"
#include <tuple>
class TypeSymbol : public Symbol {

public:
  // using ptr = std::shared_ptr<TypeSymbol>;
  static TypeSymbol::ptr create(std::string const &name,
                                Type::ptr const &type) {
    return std::make_shared<TypeSymbol>(name, type);
  }
  TypeSymbol(std::string const &name, Type::ptr const &t);
};

#endif //!__TYPE_SYMBOL_H_