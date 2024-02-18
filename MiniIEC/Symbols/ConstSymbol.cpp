
#include "Symbols/ConstSymbol.h"
ConstSymbol::ConstSymbol(std::string const &name, Type::ptr const &t)
    : mType(t), mValue(std::stoi(name)), Symbol(name, t) {}
Type::ptr ConstSymbol::getType() const { return mType; };
int ConstSymbol::getValue() const { return mValue; }