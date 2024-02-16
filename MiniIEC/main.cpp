#include "CodeGen/CodeGenRISCV.h"
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
#include "RegisterAdmin.h"
#include "SymbolTable.h"

#include "DacHelper.h"
#include "Parser.h"
#include "Scanner.h"
#include "SymbolFactory.h"
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

std::string toString(dac::Operand::ptr p) {
  auto sop = dac::extract<dac::SymbolOperand>(p);
  auto dop = dac::extract<dac::DacOperand>(p);
  if (sop != nullptr) {
    return sop->get()->GetName();
  }
  if (dop != nullptr) {
    std::string s = "";
    if (dop->isJump())
      s += "j";
    if (dop->isResult())
      s += "r";
    return std::format(" *{1}", s, dop->get()->getPosition());
  }
  return "";
}


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

  } else {
    printf("File could not be read \n");
  }

  std::cout << std::endl;
  // Dumbpsybol Table
  SymbolTable &st = SymbolTable::GetInstance();
  auto g = dach::getGen();
  g.updateIndex();

  // calculate next usage
  std::map<dac::Operand::ptr, size_t> lu;
  for (int i = g.size() - 1; i >= 0; i--) {
    auto e = (g.begin() + i);
    if (e->get()->getKind() == dac::Assign) {

      auto sop = dac::extract<dac::SymbolOperand>(e->get()->getFirst());
      if (sop != nullptr) {
        lu[e->get()->getFirst()] = 0;
      }
    } else {
      // auto f = dac::extract<dac::SymbolOperand>(e->get()->getFirst());
      if (e->get()->getFirst() != nullptr) {
        lu[e->get()->getFirst()] = i;
      }
      auto ps = e->get()->getSecond();
      if (ps != nullptr) {
        // auto s = dac::extract<dac::SymbolOperand>(ps);
        // if (s != nullptr) {
        lu[ps] = i;
        // }
      }
    }
    for (auto s : lu) {
      e->get()->addnextUsed(s.first, s.second);
    }
  }

  std::cout << std::format("{:6}: ", ' ');
  for (auto s : st) {
    std::cout << std::format("{: >6} ", s.first);
  }
  std::cout << std::endl;
  for (size_t i = 0; i < g.size(); i++) {
    auto e = *(g.begin() + i);
    std::cout << std::format("{:6}: ", i);
    for (auto s : st) {
      dac::Operand::ptr p = dac::SymbolOperand::create(s.second);
      if (e->hasNextUse(p))
        std::cout << std::format("{:6} ", e->getNextUse(p));
      else
        std::cout << std::format("{: >6} ", '-');
    }
    std::cout << dac::OpKindToString(e.get()->getKind());
    std::cout << " " << toString(e->getFirst()) << " "
              << toString(e->getSecond()) << std::endl;
  }
  MIEC::CodeGenRISCV gen{true, true};
  // using RegisterAdmin = RegisterAdmin<>;
  RegisterAdmin regadm{gen.GetRegCnt()};
  auto resultReg = dac::Entry::create(dac::OpKind::Exit);
  regadm.AssignRegister(1, resultReg);
  for (size_t i = 0; i < g.size(); i++) {
    auto e = *(g.begin() + i);
    RegisterAdmin::RegNr ra;
    RegisterAdmin::RegNr rb;
    RegisterAdmin::RegNr rc;
    dac::SymbolOperand *f1s{nullptr};
    dac::SymbolOperand *f2s;
    dac::DacOperand *f1d;
    dac::DacOperand *f2d;
    f1s = dac::extract<dac::SymbolOperand>(e->getFirst());
    f1d = dac::extract<dac::DacOperand>(e->getFirst());
    f2s = dac::extract<dac::SymbolOperand>(e->getSecond());
    f2d = dac::extract<dac::DacOperand>(e->getSecond());
    auto x = dac::DacOperand::createResult(e);
    switch (e->getKind()) {

    case dac::Add:
    case dac::Sub:
    case dac::Mult:
    case dac::Div:
      // todo: create result

      if (regadm.hasRegister(x)) {
        rc = regadm.GetRegister(x);
      } else {
        rc = regadm.AssignRegister(regadm.GetRegister(), e);
      }

    case dac::Assign:
      // create ra,rb
      //create ra
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

    //create rb
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
    case dac::IsEq:
    case dac::IsLeq:
    case dac::IsGtq:
    case dac::IsNotEq:
    case dac::IsLess:
    case dac::IsGreater:
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
    gen.Div(ra, rb, rc, 1, 2, 3);
      // TODO:
      break;
    case dac::IsEq:
      // TODO:
      break;
    case dac::IsLeq:
      // TODO:
      break;
    case dac::IsGtq:
      // TODO:
      break;
    case dac::IsNotEq:
      // TODO:
      break;
    case dac::IsLess:
      // TODO:
      break;
    case dac::IsGreater:
      // TODO:
      break;
    case dac::Assign:
    // gen.LoadI(ra, extract<VarSymbol>(f1s->get())->getOffset());
    gen.Store(rb, 0, extract<VarSymbol>(f1s->get())->getOffset());
    // std::cout<<"";
      break;
    case dac::Jump:
      // gen.Jump(BYTE aRegA, BYTE aRegTmp, WORD addr)
      break;
    case dac::IfFalse:
      break;
    case dac::Print:
      break;
    case dac::Exit:
      break;
    }
  }
  // for(auto itr=st.cbegin();itr!=st.cend();itr++)
  // {
  //   auto x=itr->second.get();
  //   VarSymbol* v=dynamic_cast<VarSymbol*>(x);
  //   TypeSymbol* t=dynamic_cast<TypeSymbol*>(x);
  //   ConstSymbol* c=dynamic_cast<ConstSymbol*>(x);
  //   if(v!=nullptr)
  //   {
  //     std::cout<<"v "<<v->getOffset()<<" ";
  //   }
  //   if(t!=nullptr)
  //   {
  //     std::cout<<"t ";
  //   }
  //   if(c!=nullptr)
  //   {
  //     std::cout<<"c ";
  //   }
  //   std::cout<<x->GetName()<<std::endl;
  // }
  std::fstream out{};
  out.open("./test");
  out << "Hallo\n";
  gen.WriteDisassembled(std::cout);
  out.close();
  out.open("./test2");
  out << "Hallo\n";
  gen.WriteExecutable(out);
  out.close();
  return 0;
}
