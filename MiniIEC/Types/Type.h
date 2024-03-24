/**
 * @file Type.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief type baseclass
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __TYPE_H__
#define __TYPE_H__

#include <cstddef>
#include <memory>

class Symbol;
/**
 * @brief type baseclass
 * 
 */
class Type {
public:
  using ptr = std::shared_ptr<Type>;
  /**
   * @brief Get the amount of bytes required in memory to store it
   * 
   * @return std::size_t 
   */
  virtual std::size_t getSize() const = 0;
  /**
   * @brief Get the Name
   * 
   * @return std::shared_ptr<Symbol> 
   */
  virtual std::shared_ptr<Symbol> getName() const = 0;
};

#endif