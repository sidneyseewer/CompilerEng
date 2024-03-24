/**
 * @file Symbol.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Base Implementation of Symbol
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "../Types/Type.h"
#include "../lib/concepts.h"
#include <memory>
#include <string>
/**
 * @brief Base Implementation of Symbol
 * 
 */
class Symbol {
private:
  std::string mNmae;
  Type::ptr mType;

protected:
/**
 * @brief Construct a new Symbol with type
 * 
 * @param name 
 * @param type 
 */
  Symbol(std::string const &name, Type::ptr const &type);

public:
  using ptr = std::shared_ptr<Symbol>;
  /**
   * @brief Get the Name
   * 
   * @return std::string 
   */
  virtual std::string GetName() const;
  /**
   * @brief Get the Type 
   * 
   * @return Type::ptr 
   */
  virtual Type::ptr getType() const;
};
/**
 * @brief converts o to Pointer of F
 * 
 * @tparam F 
 * @param o 
 * @return F* 
 */
template <Derived<Symbol> F> F *extract(std::shared_ptr<Symbol> const &o) {
  if (o != nullptr)
    return dynamic_cast<F *>(o.get());
  return nullptr;
}

#endif