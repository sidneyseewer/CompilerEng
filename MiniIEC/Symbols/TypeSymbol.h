#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/Type.h"
#include <tuple>
class TypeSymbol : public Symbol {
  Type::ptr mNameSymbol;
  public:
    static TypeSymbol::ptr create(std::string name,Type::ptr type){return std::make_shared<TypeSymbol>(name,type);}
  Type::ptr getType(){return mNameSymbol;}
  TypeSymbol(std::string name,Type::ptr t):Symbol(name,t){}
};

#endif //!__TYPE_SYMBOL_H_