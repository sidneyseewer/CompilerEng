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
    wchar_t *outputFile = coco_string_create(argv[4]);
    printf("Inputfile: %ls\n", inputFile);
    printf("Outputfile: %ls\n", outputFile);
    MIEC::Scanner *scanner = new MIEC::Scanner(inputFile);
    MIEC::Parser *parser = new MIEC::Parser(scanner);
    //		parser->tab = new MIEC::SymbolTable(parser);
    //		parser->gen = new MIEC::CodeGenerator();
    try {
      parser->Parse();
      if (parser->errors->count == 0) {
        printf("No errors detected!");
      } else {
        printf("%d errors detected", parser->errors->count);
      }
    } catch (char const *e) {
      std::cerr << e;
    }
    coco_string_delete(inputFile);
    //		delete parser->gen;
    //		delete parser->tab;
    delete parser;
    delete scanner;

    std::cout << std::endl;
    // Dumbpsybol Table
    SymbolTable &st = SymbolTable::GetInstance();
    auto g = dach::getGen();
    g.updateJumpRefs();
    g.updateIndex();

    NextUseCalc nuc{};
    nuc.Calc(g.begin(), g.end());
#ifndef NDEBUG
    prt(g, st);
#endif

size_t iterations=0;
size_t lasSize=0;
size_t currentSize=0;
do{
  lasSize=currentSize;
  iterations++;
  MIEC::CodeGenRISCV gen{false,false};
  CodeGenAdapter adp{&gen,true};
  adp.Run(g.getCode());
  currentSize=gen.GetCodePosition();
  #ifndef NDEBUG
    std::cout<<std::format("{} {}\n",iterations,currentSize);
  #endif
}while(lasSize!=currentSize);
std::cout<<"iterations: "<<iterations;
  MIEC::CodeGenRISCV gen{true,false};
  CodeGenAdapter adp{&gen,false};
  adp.Run(g.getCode());
    // for (auto j : jumps) {
    //   dac::DacOperand *x;
    //   if (j.second->getSecond() != nullptr) {
    //     x = extract<dac::DacOperand>(j.second->getSecond());
    //   } else {
    //     x = extract<dac::DacOperand>(j.second->getFirst());
    //   }
    //   if (x == nullptr)
    //     std::cerr << "Internal error\n";
    //   else
    //     // TODO: iffalsejumps are stored as results
    //     gen.SetAddress(j.first, j.first + 4); // x->getJump()->getPosition());
    // }


    /////////////////////////////
    // start a if-then-else
    /////////////////////////////
    /*
    x := 1;
    IF (x < 10) THEN
       x := x + 1;
        print (x)
    ELSE
       print (10);
    */

    /*DAC:
       x = 9
       IFFALSE x < 10 GOTO L1
          x = x + 1
          print (x)
          GOTO L2
    L1:print (10)
    L2: ...
    */
    
#ifndef NDEBUG
    std::cout << "\n\n";
    gen.WriteDisassembled(std::cout);
#endif
    std::ofstream file{argv[4]};
    if (file) {
      gen.WriteExecutable(file);
    } else {
      std::cerr << "error write text.iex" << std::endl;
      return 1;
    }

  } else {
    printf("File could not be read \n");
  }
}
