#ifndef ___VAR_SYMBOL_H__
#define ___VAR_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
class VarSymbol: public Symbol
{
    size_t mOffset;
    public:
    VarSymbol(std::string name):Symbol(name){}
    size_t getOffset(){return mOffset;};
    Type::ptr getType(){return std::make_shared<BaseType>(TypeKind::DOUBLE,12);};
};

#endif //!__VAR_SYMBOL_H_