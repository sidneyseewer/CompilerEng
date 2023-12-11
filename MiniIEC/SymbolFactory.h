#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include "lib/Singelton.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>

class SymbolFactory:public Singelton<SymbolFactory>{
    using container=std::map<TypeKind,BaseType::ptr>;
    static container types;
        static container::value_type create(TypeKind bt,size_t len){return {bt,BaseType::create(bt, len)};}
    friend class Singelton<SymbolFactory>;
    public:
    Symbol::ptr CreateVar(std::string name,TypeKind type);
    Symbol::ptr CreateConst(std::string name);
    Symbol::ptr CreateType(std::string name);
};

#endif //!__SYMBOL_FACTORY_H__
