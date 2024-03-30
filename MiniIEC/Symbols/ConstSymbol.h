/**
 * @file ConstSymbol.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Constant Symbol
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __CONST_SYMBOL_H__
#define __CONST_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include <string>
/**
 * @brief constant symbol
 * 
 */
class ConstSymbol : public Symbol {
  // Type::ptr mType;
  int mValue;

public:
  using ptr = std::shared_ptr<ConstSymbol>;
  /**
   * @brief create new const Sumbol
   * 
   * @param name 
   * @param type 
   * @return ConstSymbol::ptr 
   */
  static ConstSymbol::ptr create(std::string const &name,
                                 Type::ptr const &type) {
    return std::make_shared<ConstSymbol>(name, type);
  }
  /**
   * @brief Construct a new Constant Symbol
   * 
   * @param name 
   * @param t 
   */
  ConstSymbol(std::string const &name, Type::ptr const &t);

  /**
   * @brief Get the Value of symbol
   * 
   * @return int 
   */
  int getValue() const;
};

#endif //!__CONST_SYMBOL_H_