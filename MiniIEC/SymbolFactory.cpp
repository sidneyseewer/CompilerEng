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
    size_t digets=0;
    std::size_t points=0;
    std::size_t neg=0;
    std::size_t pos=0;
    std::size_t comas=0;
    std::size_t others=0;
    std::for_each(name.cbegin(),name.cend(),[&digets,&points,&neg,&pos,&comas,&others](char c){
        switch (c) {
        case '+':
        pos++;
        break;
        case '-':
        neg++;
        break;
        case '.':
        points++;
        break;
        case ',':
        comas++;
        break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        digets++;
        break;
        default:
    others++;
        break;
        }
    });
    Type::ptr type;
    if(others==0&&points==1)
    {
        type=types.at(FLOAT);
    }
    else if (others==0&&points==0) {
        type=types.at(INT);
    }
    else {
        type=StringType::create();
    }
    return ConstSymbol::create(name, type);
}
Symbol::ptr SymbolFactory::CreateType(string name){
    TypeKind type;
    if(name=="integer")
    {
        type=INT;
    }else if(name=="float")
    {
        type=FLOAT;
    }else if (name=="double") {
        type=DOUBLE;
    }
    else {
    throw "unknown type";
    }
    return TypeSymbol::create(name,types.at(type));
}
Symbol::ptr SymbolFactory::CreateVar(string name,TypeKind type){
    return VarSymbol::create(name,types.at(type));
}