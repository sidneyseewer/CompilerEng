#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "Symbols/Symbol.h"
#include <string>

class SymbolFactory{
    public:
    Symbol::ptr CreateVar(std::string name);
    Symbol::ptr CreateConst(std::string name);
    Symbol::ptr CreateType(std::string name);
};

#endif //!__SYMBOL_FACTORY_H__
