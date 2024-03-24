/**
 * @file BaseType.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief baseType Implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "BaseType.h"
BaseType::BaseType(TypeKind  const&kind, size_t  const&size) : mKind(kind), msize(size) {}
void BaseType::setSymbol(Symbol::ptr const& s) { mSymbol = s; }
std::size_t BaseType::getSize() const { return msize; }
Symbol::ptr BaseType::getName() const { return mSymbol; }