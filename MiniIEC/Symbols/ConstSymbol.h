#ifndef __CONST_SYMBOL_H__
#define __CONST_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include <string>

class ConstSymbol : public Symbol {
  Type::ptr mType;
  int mValue;

public:
  using ptr = std::shared_ptr<ConstSymbol>;
  static ConstSymbol::ptr create(std::string const &name,
                                 Type::ptr const &type) {
    return std::make_shared<ConstSymbol>(name, type);
  }
  ConstSymbol(std::string const &name, Type::ptr const &t);
  Type::ptr getType() const override;
  int getValue() const;
};

#endif //!__CONST_SYMBOL_H_