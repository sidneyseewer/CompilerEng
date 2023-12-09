#include "SymbolFactory.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include <memory>

using namespace std;
Symbol::ptr SymbolFactory::CreateConst(string name){
    return std::make_shared<ConstSymbol>(std::make_shared<BaseType>(TypeKind::DOUBLE),name);
}