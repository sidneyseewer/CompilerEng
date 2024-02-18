#include "TypeSymbol.h"

TypeSymbol::TypeSymbol(std::string const &name, Type::ptr const &t)
    : Symbol(name, t) {}