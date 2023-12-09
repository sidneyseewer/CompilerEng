#include "SymbolFactory.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include <memory>

using namespace std;
Symbol::ptr SymbolFactory::CreateConst(string name){
    return std::make_shared<ConstSymbol>(name,std::make_shared<BaseType>(TypeKind::DOUBLE,12));
}
Symbol::ptr SymbolFactory::CreateType(string name){
    return std::make_shared<TypeSymbol>(name);
}
Symbol::ptr SymbolFactory::CreateVar(string name){
    return std::make_shared<VarSymbol>(name);
}