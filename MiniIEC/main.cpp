/**
 * @file main.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief
 * @version 0.1
 * @date 2024-03-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "CodeGen/CodeGenRISCV.h"
#include "CodeGenAdapter.h"
#include "DacHelper.h"
#include "NextUseCalc.h"
#include "Parser.h"
#include "Scanner.h"
#include "SymbolFactory.h"
#include "SymbolTable.h"
#include "Symbols/ConstSymbol.h"
#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Symbols/VarSymbol.h"
#include "Types/BaseType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include "dac/Entry.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "lib/Singelton.h"
#include "lib/helper.h"
#include "stdio.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <ostream>
#include <string>
#include <sys/timeb.h>
#include <utility>
#include <vector>
#include <wchar.h>

#include <format>

#include "dac/Operands/DacOperand.h"
#include "dac/Operands/SymbolOperand.h"

// commnet out for debug output 
#define NDEBUG

int main(int argc, char *argv[])
{
  if (argc >= 5)
  {
    std::cout<<std::format("parsing {}\n",argv[2]);
    wchar_t *inputFile = coco_string_create(argv[2]);
    std::string outputFile{argv[4]};
    MIEC::Scanner scanner{inputFile};
    dac::Generator gen{};
      SymbolTable &st = SymbolTable::GetInstance();
    DacHelper helper{
      gen,
      SymbolFactory::GetInstance(),
      st
      #ifndef NDEBUG
      ,true
      #endif
    };
    MIEC::Parser parser{&scanner, helper};
    //		parser.tab = new MIEC::SymbolTable(parser);
    //		parser.gen = new MIEC::CodeGenerator();
    try
    {
      parser.Parse();
      if (parser.errors->count == 0)
      {
        std::wcout << L"no errors detected"<<std::endl;
      }
      else
      {
        std::wcerr << parser.errors->count<<L" errors detected"<<std::endl;
      }
    }
    catch (char const *e)
    {
      std::cerr << e;
    }
    coco_string_delete(inputFile);

    std::cout << std::endl;

    if (parser.errors->count != 0)
    {
      return -1;
    }
    else
    {

      // Dumbpsybol Table
      gen.updateJumpRefs();
      gen.updateIndex();

      NextUseCalc nuc{};
      nuc.Calc(gen.cbegin(), gen.cend());
#ifndef NDEBUG
      std::wcout << "NextUsage Table dac line count\n"
                << std::flush;
      prt(gen, st, std::wcout);
#endif

      size_t iterations = 0;
      size_t lasSize = 0;
      size_t currentSize = 0;
      do
      {
        lasSize = currentSize;
        iterations++;
        MIEC::CodeGenRISCV gen2{false, false};

        CodeGenAdapter adp{&gen2, true};
        adp.Run(gen.getCode());
        currentSize = gen2.GetCodePosition();
#ifndef NDEBUG
        std::cout << std::format("{} {}\n", iterations, currentSize);
#endif
      } while (lasSize != currentSize);
#ifndef NDEBUG
      std::cout << "iterations: " << iterations;
      std::cout << "\n\nNextUsage Table asmebler line count\n";
      prt(gen, st);
#endif
      MIEC::CodeGenRISCV cgen{true, false};
      CodeGenAdapter adp{&cgen, false};

      adp.Run(gen.getCode());

#ifndef NDEBUG
      std::cout << "\n\ndissasembly:\n";
      cgen.WriteDisassembled(std::cerr);
#endif
      std::ofstream file{argv[4]};
      if (file)
      {
        cgen.WriteExecutable(file);
      }
      else
      {
        std::cerr << "error write "<<argv[4] << std::endl;
        return 1;
      }
    }
  }
  else
  {
    std::cerr << "wrong amount of args \n";
  }
}
