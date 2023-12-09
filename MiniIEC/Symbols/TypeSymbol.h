#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
class TypeSymbol : public Symbol {
  Type::ptr mNameSymbol;
  public:
  Type::ptr getType(){return mNameSymbol;}
  TypeSymbol(std::string name):Symbol(name){}
};

#endif //!__TYPE_SYMBOL_H_