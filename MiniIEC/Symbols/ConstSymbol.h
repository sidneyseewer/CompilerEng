#ifndef __CONST_SYMBOL_H__
#define __CONST_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include <string>

class ConstSymbol: public Symbol
{
    Type::ptr mType;
    public:
    ConstSymbol(Type::ptr t,std::string name):mType(t),Symbol(name){}
    virtual Type::ptr getType(){return mType;};
};

#endif //!__CONST_SYMBOL_H_