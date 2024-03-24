/**
 * @file VarSymbol.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Variable Symbol implementaion
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "VarSymbol.h"

VarSymbol::VarSymbol(std::string const &name, Type::ptr const &t,
                     size_t const &offset)
    : Symbol(name, t), mOffset(offset) {}
size_t VarSymbol::getOffset() const { return mOffset; };