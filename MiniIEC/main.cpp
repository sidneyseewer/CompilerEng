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

int main(int argc, char *argv[]) {

  if (argc >= 5) {
    wchar_t *inputFile = coco_string_create(argv[2]);
    std::string outputFile{argv[4]};
    MIEC::Scanner scanner{inputFile};
    dac::Generator gen{};
    DacHelper helper{gen};
    MIEC::Parser parser{&scanner, helper};
    //		parser.tab = new MIEC::SymbolTable(parser);
    //		parser.gen = new MIEC::CodeGenerator();
    try {
      parser.Parse();
      if (parser.errors->count == 0) {
        std::cout<<std::format("no errors detected\n",parser.errors->count);
      } else {
        std::cerr<<std::format("{} errors detected\n",parser.errors->count);
      }
    } catch (char const *e) {
      std::cerr << e;
    }
    coco_string_delete(inputFile);

    std::cout << std::endl;
    // Dumbpsybol Table
    SymbolTable &st = SymbolTable::GetInstance();
    auto g = gen;
    g.updateJumpRefs();
    g.updateIndex();

    NextUseCalc nuc{};
    nuc.Calc(g.begin(), g.end());
#ifndef NDEBUG
    std::cout<<"NextUsage Table dac line count\n";
    prt(g, st);
#endif

    size_t iterations = 0;
    size_t lasSize = 0;
    size_t currentSize = 0;
    do {
      lasSize = currentSize;
      iterations++;
      MIEC::CodeGenRISCV gen{false, false};

      CodeGenAdapter adp{&gen, true};
      adp.Run(g.getCode());
      currentSize = gen.GetCodePosition();
#ifndef NDEBUG
      std::cout << std::format("{} {}\n", iterations, currentSize);
#endif
    } while (lasSize != currentSize);
#ifndef NDEBUG
    std::cout << "iterations: " << iterations;
    std::cout<<"\n\nNextUsage Table asmebler line count\n";
    prt(g, st);
#endif
    MIEC::CodeGenRISCV cgen{true, false};
    CodeGenAdapter adp{&cgen, false};

    adp.Run(g.getCode());
 
#ifndef NDEBUG
    std::cout<<"\n\ndissasembly:\n";
    gen.WriteDisassembled(std::cout);
#endif
    std::ofstream file{argv[4]};
    if (file) {
      cgen.WriteExecutable(file);
    } else {
      std::cerr << "error write text.iex" << std::endl;
      return 1;
    }

  } else {
    std::cerr<<"File could not be read \n";
  }
}
