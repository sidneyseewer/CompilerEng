#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
#include <tuple>
class TypeSymbol : public Symbol {
  Type::ptr mNameSymbol;
  public:
    static TypeSymbol::ptr create(std::string name){return std::make_shared<TypeSymbol>(name);}
  Type::ptr getType(){return mNameSymbol;}
  TypeSymbol(std::string name):Symbol(name){}
};

#endif //!__TYPE_SYMBOL_H_