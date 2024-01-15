#ifndef __DAC_SYMBOL_OPERAND_H__
#define __DAC_SYMBOL_OPERAND_H__

#include "Symbols/Symbol.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class SymbolOperand:public Operand{
    Symbol::ptr mSymbol;
    public:
    void x() override{};
    using ptr=std::shared_ptr<SymbolOperand>;
    SymbolOperand(Symbol::ptr s):mSymbol(s){}
    static ptr create(Symbol::ptr s){return std::make_shared<SymbolOperand>(s);}
};
}

#endif //!__DAC_SYMBOL_OPERAND_H__