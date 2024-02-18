#include "SymbolOperand.h"
using namespace dac;

Symbol::ptr SymbolOperand::get() const{ return mSymbol; }
SymbolOperand::SymbolOperand(Symbol::ptr  const&s) : mSymbol(s) {}