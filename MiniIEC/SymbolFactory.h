#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include "lib/Singelton.h"
#include <string>
#include <vector>

class SymbolFactory:public Singelton<SymbolFactory>{
    std::vector<BaseType::ptr> types{
        BaseType::create(INT, 4),
        BaseType::create(FLOAT, 4),
        BaseType::create(DOUBLE, 8)
        };
    public:
    Symbol::ptr CreateVar(std::string name);
    Symbol::ptr CreateConst(std::string name);
    Symbol::ptr CreateType(std::string name);
};

#endif //!__SYMBOL_FACTORY_H__
