#include "SymbolFactory.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

using namespace std;


Symbol::ptr SymbolFactory::CreateConst(string name){
    
    return ConstSymbol::create(name, mTypeSymbol->getType());
}
Symbol::ptr SymbolFactory::CreateType(string name){
    auto type=INT;
    return TypeSymbol::create(name,mTypeSymbol->getType());
}
Symbol::ptr SymbolFactory::CreateVar(string name){
    std::size_t offset=mOffset;
    auto a=mTypeSymbol->getType();
    auto b=a->getSize();
    mOffset+=b;
    return VarSymbol::create(name,mTypeSymbol->getType(),offset);
}