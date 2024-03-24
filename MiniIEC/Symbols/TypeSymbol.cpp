/**
 * @file TypeSymbol.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Type Symbol implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "TypeSymbol.h"

TypeSymbol::TypeSymbol(std::string const &name, Type::ptr const &t)
    : Symbol(name, t) {}