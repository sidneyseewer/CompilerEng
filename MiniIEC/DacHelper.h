/**
 * @file DacHelper.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief helper functions called from Coco
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __DAC_HELPER_H__
#define __DAC_HELPER_H__
#include "Scanner.h"
#include "SymbolFactory.h"
#include "SymbolTable.h"
#include "dac/Entry.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <cstddef>
#include <cwchar>
#include <format>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include "Object.h"
/**
 * @brief helper functions called from Coco
 * 
 */
class DacHelper :Object{

public:
  using errorHandler = std::function<void(wchar_t const *const)>;

private:
/**
 * @brief print to cout
 * 
 * @param t 
 * @param s 
 */
  void prt(MIEC::Token *t, wchar_t const *const s);

  dac::Generator &gen;
  SymbolFactory &factory;
  SymbolTable &symbolTable;
  errorHandler e;

public:
  void setErrorHandler(errorHandler e);
  DacHelper(dac::Generator &gen,
            SymbolFactory &fac = SymbolFactory::GetInstance(),
            SymbolTable &st = SymbolTable::GetInstance());
            /**
             * @brief Get the Gen singelton
             * 
             * @return dac::Generator&& 
             */
  dac::Generator &&getGen();
  /**
   * @brief reset generator
   * 
   */
  void resetGen();
  /**
   * @brief assignment
   * 
   * @param t 
   */
  void ass(MIEC::Token *t);
  /**
   * @brief factor
   * 
   * @param t 
   */
  void fac(MIEC::Token *t);
  /**
   * @brief factor operation
   * 
   * @param t 
   */
  void fop(MIEC::Token *t);
  /**
   * @brief left perantethies
   * 
   */
  void lpr();
  /**
   * @brief right perantethies
   * 
   */
  void rpr();
  /**
   * @brief term operator
   * 
   * @param t 
   */
  void top(MIEC::Token *t);
  /**
   * @brief end statement
   * 
   */
  void end();
  /**
   * @brief while end statement
   * 
   */
  void wend();
  /**
   * @brief if end statement
   * 
   */
  void ifend();
  /**
   * @brief while
   * 
   */
  void wle();
  /**
   * @brief else
   * 
   */
  void els();
  /**
   * @brief if
   * 
   */
  void iff();
  /**
   * @brief then
   * 
   */
  void thn();
  /**
   * @brief semicolon
   * 
   */
  void sem();
  /**
   * @brief print
   * 
   */
  void prt();
  /**
   * @brief do
   * 
   */
  void doo();
  /**
   * @brief relative operator (compare)
   * 
   * @param t 
   */
  void rop(MIEC::Token *t);
  /**
   * @brief verfy if var symbol is valid
   * 
   * @param t 
   */
  void verifyVarSymbol(MIEC::Token*t);
  /**
   * @brief add Const Symbol to symbol table
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr addConstSymbol(std::string const &name);
  /**
   * @brief add Var symbol to symbol table
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr addVarSymbol(std::string const &name);
  /**
   * @brief add type symbol to symbol table
   * 
   * @param name 
   * @return Symbol::ptr 
   */
  Symbol::ptr addTypeSymbol(std::string const &name);
};
#endif //!__DAC_HELPER_H__