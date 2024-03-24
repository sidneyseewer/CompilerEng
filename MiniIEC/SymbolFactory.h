/**
 * @file SymbolFactory.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Symbol factory
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __SYMBOL_FACTORY_H__
#define __SYMBOL_FACTORY_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/BaseType.h"
#include "Types/TypeKind.h"
#include "lib/Singelton.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>
/**
 * @brief Symbol Factory
 * 
 */
class SymbolFactory : public Singelton<SymbolFactory> {
  friend class Singelton<SymbolFactory>;
  TypeSymbol::ptr mTypeSymbol;
  size_t mOffset = 0;

public:
  SymbolFactory();
  /**
   * @brief Create a Variable Symbol
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr CreateVar(std::string const &name);
  /**
   * @brief Create a Constant Symbol
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr CreateConst(std::string const &name);
  /**
   * @brief Create a Type Symbol
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr CreateType(std::string const &name);
};

#endif //!__SYMBOL_FACTORY_H__
