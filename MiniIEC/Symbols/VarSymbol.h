#ifndef ___VAR_SYMBOL_H__
#define ___VAR_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
#include <string>
class VarSymbol: public Symbol
{
    size_t mOffset;
    public:
    static VarSymbol::ptr create(std::string name,Type::ptr type){return std::make_shared<TypeSymbol>(name,type);}
    VarSymbol(std::string name,Type::ptr t):Symbol(name,t){}
    size_t getOffset(){return mOffset;};
};

#endif //!__VAR_SYMBOL_H_