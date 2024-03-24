
/**
 * @file ConstSymbol.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Constant Symbol
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Symbols/ConstSymbol.h"
ConstSymbol::ConstSymbol(std::string const &name, Type::ptr const &t)
    : mType(t), mValue(std::stoi(name)), Symbol(name, t) {}
Type::ptr ConstSymbol::getType() const { return mType; };
int ConstSymbol::getValue() const { return mValue; }