#include "SymbolFactory.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include "Types/StringType.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

using namespace std;

SymbolFactory::container SymbolFactory::types{
        create(INT, 4),
        create(FLOAT, 4),
        create(DOUBLE, 8)
        };

Symbol::ptr SymbolFactory::CreateConst(string name){
    auto type=types.at(INT);
    
    return ConstSymbol::create(name, type);
}
Symbol::ptr SymbolFactory::CreateType(string name){
    auto type=INT;
    return TypeSymbol::create(name,types.at(type));
}
Symbol::ptr SymbolFactory::CreateVar(string name,TypeKind type){
    return VarSymbol::create(name,types.at(type));
}