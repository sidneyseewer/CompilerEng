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

class DacHelper {

public:
  using errorHandler = std::function<void(wchar_t const *const)>;

private:
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
  dac::Generator &&getGen();
  void resetGen();
  void ass(MIEC::Token *t);
  void fac(MIEC::Token *t);
  void fop(MIEC::Token *t);
  void lpr();
  void rpr();
  void top(MIEC::Token *t);
  void end();
  void wend();
  void ifend();
  void wle();
  void els();
  void iff();
  void thn();
  void sem();
  void prt();
  void doo();
  void rop(MIEC::Token *t);

  Symbol::ptr addConstSymbol(std::string const &name);
  Symbol::ptr addVarSymbol(std::string const &name);
  Symbol::ptr addTypeSymbol(std::string const &name);
};
#endif //!__DAC_HELPER_H__