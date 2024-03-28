/**
 * @file SymbolTable.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Symboltable
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "Symbols/Symbol.h"
#include "lib/Singelton.h"
#include "Object.h"
#include <string>
#include <unordered_map>

class Parser;
class Errors;

// Singleton class SymbolTable
class SymbolTable : public Singelton<SymbolTable>,Object {
public:
  // Method to add a symbol to the table
  void Add(Symbol::ptr symbol);

  // Method to find a symbol in the table
  Symbol::ptr Find(const std::string &name);
  /**
   * @brief add a new symbol
   * 
   * @param identifier 
   * @param dataType 
   */
  void insert(const std::string &identifier, Symbol::ptr const &dataType);
  /**
   * @brief check if symbol exists
   * 
   * @param identifier 
   * @param entry 
   * @return true 
   * @return false 
   */
  bool lookup(const std::string &identifier, Symbol::ptr const &entry) const;
  //iteratable
  using container = std::unordered_map<std::string, Symbol::ptr>;
  container::const_iterator cbegin() const;
  container::const_iterator cend() const;
  container::iterator begin();
  container::iterator end();

private:
  friend class Singelton<SymbolTable>;
  // Private constructor to enforce singleton pattern
  int currentOffset; // Member to track current offset

  container symbols;
};

#endif //! SYMBOLTABLE_H
