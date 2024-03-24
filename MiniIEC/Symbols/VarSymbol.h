/**
 * @file VarSymbol.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief variable Symbol Implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ___VAR_SYMBOL_H__
#define ___VAR_SYMBOL_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
#include <string>
/**
 * @brief variable Symbol Implementation
 * 
 */
class VarSymbol : public Symbol {
public:
  using ptr = std::shared_ptr<VarSymbol>;

private:
  size_t mOffset;

public:
/**
 * @brief Construct a new Variable Symbol
 * 
 * @param name 
 * @param t 
 * @param offset 
 */
  VarSymbol(std::string const &name, Type::ptr const &t, size_t const &offset);
  /**
   * @brief create a new Variable Symbol
   * 
   * @param name 
   * @param type 
   * @param offset 
   * @return VarSymbol::ptr 
   */
  static VarSymbol::ptr create(std::string const &name, Type::ptr const &type,
                               size_t const &offset) {
    return std::make_shared<VarSymbol>(name, type, offset);
  }
  /**
   * @brief Get the Offset in memory
   * 
   * @return size_t 
   */
  size_t getOffset()const;
};

#endif //!__VAR_SYMBOL_H_