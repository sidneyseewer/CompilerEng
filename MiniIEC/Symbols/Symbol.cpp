/**
 * @file Symbol.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Symbol.h"

Symbol::Symbol(std::string const &name, Type::ptr const &type)
    : mNmae(name), mType(type) {}

std::string Symbol::GetName() const { return mNmae; };
Type::ptr Symbol::getType() const { return mType; };