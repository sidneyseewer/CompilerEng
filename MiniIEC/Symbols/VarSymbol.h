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
  using ptr = std::shared_ptr<VarSymbol>;
    static VarSymbol::ptr create(std::string name,Type::ptr type,size_t offset){return std::make_shared<VarSymbol>(name,type,offset);}
    VarSymbol(std::string name,Type::ptr t,size_t offset):Symbol(name,t),mOffset(offset){}
    size_t getOffset(){return mOffset;};
};

#endif //!__VAR_SYMBOL_H_