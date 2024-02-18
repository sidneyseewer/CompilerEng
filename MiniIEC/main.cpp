#include "CodeGen/CodeGenRISCV.h"
#include "DacHelper.h"
#include "NextUseCalc.h"
#include "Parser.h"
#include "RegisterAdmin.h"
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
    // std::cout << std::format("{:6}: ", ' ');
    // for (auto s : st) {
    //   std::cout << std::format("{: >6} ", s.first);
    // }for (auto s : g) {
    //   std::cout << std::format("&{: <6} ", s->getPosition());
    // }
    // std::cout << std::endl;
    // for (size_t i = 0; i < g.size(); i++) {
    //   auto e = *(g.begin() + i);
    //   std::cout << std::format("{:6}: ", i);
    //   for (auto s : st) {
    //     dac::Operand::ptr p = dac::SymbolOperand::create(s.second);
    //     if (e->hasNextUse(p))
    //       std::cout << std::format("{:6} ", e->getNextUse(p));
    //     else
    //       std::cout << std::format("{: >6} ", '-');
    //   }
    //   for (auto s : g) {
    //     dac::Operand::ptr p = dac::DacOperand::createResult(s);
    //     if (e->hasNextUse(p))
    //       std::cout << std::format("{:6} ", e->getNextUse(p));
    //     else
    //       std::cout << std::format("{: >6} ", '-');
    //   }
    //   std::cout << dac::OpKindToString(e.get()->getKind());
    //   std::cout << " " << toString(e->getFirst()) << " "
    //             << toString(e->getSecond()) << std::endl;
    // }

    // TODO: a=a; crashed
    MIEC::CodeGenRISCV gen{true, true};
    // using RegisterAdmin = RegisterAdmin<>;
    RegisterAdmin regadm{gen.GetRegCnt()};
    auto temRegInstruction = dac::Entry::create(dac::OpKind::Exit);
    auto tempReg = regadm.GetRegister();
    regadm.AssignRegister(tempReg, temRegInstruction);

    std::vector<std::pair<CodeGen<int32_t>::WORD, dac::Entry::ptr>> jumps{};
    for (size_t i = 0; i < g.size(); i++) {
      auto e = *(g.begin() + i);
      RegisterAdmin::RegNr ra = 0;
      RegisterAdmin::RegNr rb = 0;
      RegisterAdmin::RegNr rc = 0;
      dac::SymbolOperand *f1s{nullptr};
      dac::SymbolOperand *f2s;
      dac::DacOperand *f1d;
      dac::DacOperand *f2d;
      f1s = dac::extract<dac::SymbolOperand>(e->getFirst());
      f1d = dac::extract<dac::DacOperand>(e->getFirst());
      f2s = dac::extract<dac::SymbolOperand>(e->getSecond());
      f2d = dac::extract<dac::DacOperand>(e->getSecond());
      auto x = dac::DacOperand::createResult(e);
      e->setPosition(gen.GetCodePosition());
      switch (e->getKind()) {

      case dac::Add:
      case dac::Sub:
      case dac::Mult:
      case dac::Div:
        // create result

        if (regadm.hasRegister(x)) {
          rc = regadm.GetRegister(x);
        } else {
          rc = regadm.AssignRegister(regadm.GetRegister(), e);
        }

      case dac::Assign:
      case dac::IsEq:
      case dac::IsLeq:
      case dac::IsGtq:
      case dac::IsNotEq:
      case dac::IsLess:
      case dac::IsGreater:
        // create ra,rb
        // create ra
        if (f1s != nullptr) {
          if (regadm.hasRegister(e->getFirst())) {
            ra = regadm.GetRegister(e->getFirst());
          } else {
            ra = regadm.AssignRegister(regadm.GetRegister(), f1s->get());
            auto constsym = extract<ConstSymbol>(f1s->get());
            auto varsym = extract<VarSymbol>(f1s->get());
            if (constsym != nullptr)
              gen.LoadI(ra, constsym->getValue());
            if (varsym != nullptr)
              gen.Load(ra, 0, varsym->getOffset());
          }
        } else if (f1d != nullptr) {
          if (regadm.hasRegister(e->getFirst())) {
            ra = regadm.GetRegister(e->getFirst());
          } else {
            throw "required value does not exist";
          }
        }

      case dac::Print:
        // create rb
        if (f2s != nullptr) {
          if (regadm.hasRegister(e->getSecond())) {
            rb = regadm.GetRegister(e->getSecond());
          } else {
            rb = regadm.AssignRegister(regadm.GetRegister(), f2s->get());
            auto constsym = extract<ConstSymbol>(f2s->get());
            auto varsym = extract<VarSymbol>(f2s->get());
            if (constsym != nullptr)
              gen.LoadI(rb, constsym->getValue());
            if (varsym != nullptr)
              gen.Load(rb, 0, varsym->getOffset());
          }
        } else if (f2d != nullptr) {
          if (regadm.hasRegister(e->getSecond())) {
            rb = regadm.GetRegister(e->getSecond());
          } else {
            throw "required value does not exist";
          }
        }
        break;
      case dac::Jump:
      case dac::IfFalse:
      case dac::Exit:
        break;
      }

      switch (e->getKind()) {
      case dac::IsEq:
      case dac::IsLeq:
      case dac::IsGtq:
      case dac::IsNotEq:
      case dac::IsLess:
      case dac::IsGreater:
        i++;
        (g.begin() + i)->get()->setPosition(e->getPosition());
        break;

      case dac::Add:
      case dac::Sub:
      case dac::Mult:
      case dac::Div:
      case dac::Assign:
      case dac::Jump:
      case dac::IfFalse:
      case dac::Print:
      case dac::Exit:
        break;
      }
      switch (e->getKind()) {

      case dac::Add:
        gen.Add(ra, rb, rc);
        break;
      case dac::Sub:
        gen.Sub(ra, ra, rc);
        break;
      case dac::Mult:
        gen.Mul(ra, rb, rc, 1);
        break;
      case dac::Div:
        gen.Div(ra, rb, rc, tempReg, tempReg, tempReg);
        // TODO:
        break;
      case dac::IfFalse:
        break;

      case dac::Assign:
        // gen.LoadI(ra, extract<VarSymbol>(f1s->get())->getOffset());
        gen.Store(rb, 0, extract<VarSymbol>(f1s->get())->getOffset());
        // std::cout<<"";
        break;
      case dac::Jump:
        jumps.emplace_back(gen.Jump(tempReg, tempReg, 0), e);
        break;
        break;
      case dac::Print:
        gen.PrintInt(ra);
        break;
      case dac::Exit:
        gen.Sleep();
        break;
      case dac::IsEq:
        // jumps.emplace_back(Args &&args...)
        jumps.emplace_back(gen.JumpEQ(ra, rb, tempReg, 0), *(g.begin() + i));
        break;
      case dac::IsLeq:
        jumps.emplace_back(gen.JumpLE(ra, rb, tempReg, 0), *(g.begin() + i));
        break;
      case dac::IsGtq:
        jumps.emplace_back(gen.JumpGE(ra, rb, tempReg, 0), *(g.begin() + i));
        break;
      case dac::IsNotEq:
        jumps.emplace_back(gen.JumpNEQ(ra, rb, tempReg, 0),
                           *(g.begin() + i + 1));
        break;
      case dac::IsLess:
        jumps.emplace_back(gen.JumpL(ra, rb, tempReg, 0), *(g.begin() + i + 1));
        break;
      case dac::IsGreater:
        jumps.emplace_back(gen.JumpG(ra, rb, tempReg, 0), *(g.begin() + i + 1));
        break;
        break;
      }
      if (!e->hasNextUse(e->getFirst()) && ra != 0) {
        regadm.FreeRegister(ra);
      }

      if (!e->hasNextUse(e->getSecond()) && rb != 0) {
        regadm.FreeRegister(rb);
      }
      if (!e->hasNextUse(dac::DacOperand::createResult(e)) && rc != 0) {
        regadm.FreeRegister(rc);
      }
    }
    for (auto j : jumps) {
      dac::DacOperand *x;
      if (j.second->getSecond() != nullptr) {
        x = extract<dac::DacOperand>(j.second->getSecond());
      } else {
        x = extract<dac::DacOperand>(j.second->getFirst());
      }
      if (x == nullptr)
        std::cerr << "Internal error\n";
      else
        // TODO: iffalsejumps are stored as results
        gen.SetAddress(j.first, j.first + 4); // x->getJump()->getPosition());
    }


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
