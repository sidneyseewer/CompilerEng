#include "BaseType.h"
BaseType::BaseType(TypeKind  const&kind, size_t  const&size) : mKind(kind), msize(size) {}
void BaseType::setSymbol(Symbol::ptr const& s) { mSymbol = s; }
std::size_t BaseType::getSize() const { return msize; }
Symbol::ptr BaseType::getName() const { return mSymbol; }