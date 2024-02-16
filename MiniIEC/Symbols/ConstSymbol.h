#ifndef __CONST_SYMBOL_H__
#define __CONST_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include <string>

class ConstSymbol: public Symbol
{
    Type::ptr mType;
    int mValue;
    public:
    using ptr = std::shared_ptr<ConstSymbol>;
    static ConstSymbol::ptr create(std::string name,Type::ptr type){return std::make_shared<ConstSymbol>(name,type);}
    ConstSymbol(std::string name,Type::ptr t):mType(t),mValue(std::stoi(name)),Symbol(name,t){}
    Type::ptr getType() const override{return mType;};
    int getValue(){return mValue;}
};

#endif //!__CONST_SYMBOL_H_