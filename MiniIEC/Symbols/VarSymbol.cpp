#include "VarSymbol.h"

VarSymbol::VarSymbol(std::string const &name, Type::ptr const &t,
                     size_t const &offset)
    : Symbol(name, t), mOffset(offset) {}
size_t VarSymbol::getOffset() const { return mOffset; };