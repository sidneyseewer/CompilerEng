/**
 * @file CodeGenAdapter.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief code gen Adapter
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CODE_GEN_ADAPTER_H__
#define __CODE_GEN_ADAPTER_H__

#include "CodeGen/CodeGen.h"
#include "RegisterAdmin.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/VarSymbol.h"
#include "dac/Entry.h"
#include "dac/OpKind.h"
#include <cassert>
#include <cstdint>
#include "Object.h"
/**
 * @brief generate bytecode from Entry list
 * 
 */
class CodeGenAdapter :Object{
  bool dryRun;
  CodeGen<int32_t> *gen;

public:
  CodeGenAdapter(CodeGen<int32_t> *pgen, bool const& dryRun);
  void Run(std::vector<dac::Entry::ptr> const &g);
};

#endif //!__CODE_GEN_ADAPTER_H__