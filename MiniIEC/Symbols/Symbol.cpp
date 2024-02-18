#include "Symbol.h"

Symbol::Symbol(std::string const &name, Type::ptr const &type)
    : mNmae(name), mType(type) {}

std::string Symbol::GetName() const { return mNmae; };
Type::ptr Symbol::getType() const { return mType; };