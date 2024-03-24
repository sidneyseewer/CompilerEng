/**
 * @file TypeSymbol.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Type Symbol
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TYPE_SYMBOL_H__
#define __TYPE_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/Type.h"
#include <tuple>
/**
 * @brief Type Symbol
 * 
 */
class TypeSymbol : public Symbol {

public:
/**
 * @brief create new Type Symbol
 * 
 * @param name 
 * @param type 
 * @return TypeSymbol::ptr 
 */
  static TypeSymbol::ptr create(std::string const &name,
                                Type::ptr const &type) {
    return std::make_shared<TypeSymbol>(name, type);
  }
  /**
   * @brief Construct a new Type Symbol
   * 
   * @param name 
   * @param t 
   */
  TypeSymbol(std::string const &name, Type::ptr const &t);
};

#endif //!__TYPE_SYMBOL_H_