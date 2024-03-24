/**
 * @file SymbolOperand.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Symbol Refference Operand implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "SymbolOperand.h"
using namespace dac;

Symbol::ptr SymbolOperand::get() const{ return mSymbol; }
SymbolOperand::SymbolOperand(Symbol::ptr  const&s) : mSymbol(s) {}