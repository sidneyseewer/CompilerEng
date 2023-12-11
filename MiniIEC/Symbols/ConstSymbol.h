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
    static ConstSymbol::ptr create(std::string name,Type::ptr type){return std::make_shared<ConstSymbol>(name,type);}
    ConstSymbol(std::string name,Type::ptr t):mType(t),Symbol(name,t){}
    virtual Type::ptr getType(){return mType;};
    int getValue();
};

#endif //!__CONST_SYMBOL_H_