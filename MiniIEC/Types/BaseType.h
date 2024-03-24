/**
 * @file BaseType.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
/**
 * @brief 
 * 
 */
class BaseType : public Type {
public:
  using ptr = std::shared_ptr<BaseType>;

private:
  const TypeKind mKind;
  const size_t msize;
  Symbol::ptr mSymbol;

public:
/**
 * @brief Construct a new Base Type
 * 
 * @param kind 
 * @param size 
 */
  BaseType(TypeKind const &kind, size_t const &size);
  /**
   * @brief create a new Base Type
   * 
   * @param kind 
   * @param size 
   * @return BaseType::ptr 
   */
  static BaseType::ptr create(TypeKind const &kind, size_t const &size) {
    return std::make_shared<BaseType>(kind, size);
  }
  /**
   * @brief Set the Symbol
   * 
   * @param s 
   */
  void setSymbol(Symbol::ptr const &s);
  /**
   * @brief Get the Size
   * 
   * @return std::size_t 
   */
  std::size_t getSize() const override;
  /**
   * @brief Get the Name
   * 
   * @return Symbol::ptr 
   */
  Symbol::ptr getName() const override;
};

#endif //!__BASE_TYPE_H__