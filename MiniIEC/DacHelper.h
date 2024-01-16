#ifndef __DAC_HELPER_H__
#define __DAC_HELPER_H__
#include "Scanner.h"
#include "SymbolTable.h"
#include "dac/Entry.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <cstddef>
#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
class dach {
  static void prt(MIEC::Token *t, wchar_t *s) {

    // if (!tis.func.empty()) {
    //   char f = ' ';
    //   // switch (tis.func.back().f) {
    //   // case A:
    //   //   f = 'A';
    //   //   break;
    //   // case W:
    //   //   f = 'W';
    //   //   break;
    //   // case I:
    //   //   f = 'I';
    //   //   break;
    //   // case P:
    //   //   f = 'P';
    //   //   break;
    //   // }
    //   std::cout << std::format("{}({}) ", f, tis.func.back().x);
    // }
    
    // std::wcout << s << " ";
    // if (t != nullptr)
    //   std::wcout << t->val;

    // std::cout << std::endl;
  }

  static void print(dac::Entry::ptr e)
  {
    if(e->getFirst()!=nullptr)
    {
        print(e->getFirst());
    }
    if(e->getSecond()!=nullptr)
    {
        print(e->getSecond());
    }
  }
  static void print (dac::Operand::ptr e){
    
  }
//   dac::Entry::ptr root(){
//     return rootStack.back();
//   }
//   dac::Entry::ptr current(){
//     return  currents.back();
//   }
//   void root(dac::Entry::ptr e){rootStack.push_back(e);}
//   void current(dac::Entry::ptr e){currents.push_back(e);}
  static dac::Generator gen;

public:
  static void ass(MIEC::Token *t) {
    auto tmp = SymbolTable::GetInstance().Find(coco_string_create_char(t->val));
    gen.add(dac::OpKind::Assign,dac::SymbolOperand::create(tmp));
    prt(t, L"ass");
  }
  static void fac(MIEC::Token *t) {
    auto tmp = SymbolTable::GetInstance().Find(coco_string_create_char(t->val));
    gen.add(dac::SymbolOperand::create(tmp));
    prt(t, L"fac");
  }
  static void fop(MIEC::Token *t) {
    dac::OpKind kind;
    switch (*t->val) {
    case L'*':
      kind = dac::OpKind::Mult;
      break;
    case L'/':
      kind = dac::OpKind::Div;
      break;
    default:
      throw ""; // TODO:
    }
    gen.addf(kind);
    prt(t, L"fop");
  }
  static void lpr() {
    gen.pushPr();
    prt(nullptr, L"lpr"); }
  static void rpr() { 
    gen.popPr();
    prt(nullptr, L"rpr"); }
  static void top(MIEC::Token *t) { 
    dac::OpKind kind;
    switch (*t->val) {
    case L'+':
      kind = dac::OpKind::Add;
      break;
    case L'-':
      kind = dac::OpKind::Sub;
      break;
    default:
      throw ""; // TODO:
    }
    gen.addt(kind);
    prt(t, L"top"); }
  static void end() {
    
    prt(NULL, L"end");
  }static void wend() {
    gen.add(dac::OpKind::Jump,gen.ContextGetIndex());
    gen.ContextRef();
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"end");
  }static void ifend() {
    gen.ContextRef();
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"end");
  }
  static void wle() {
    gen.pushContext();
    gen.ContextSetIndex();
    prt(NULL, L"wle");
  }
  static void els() { 
    gen.add(dac::OpKind::Jump);
    gen.ContextRef();
    gen.ContextSetRef();
    prt(NULL, L"els"); }
  static void iff() {
    gen.pushContext();
    gen.ContextSetIndex();
    prt(NULL, L"iff");
  }
  static void thn() {
    gen.add(dac::OpKind::IfFalse);
    gen.ContextSetRef();
    prt(NULL, L"thnx"); }
  static void sem(MIEC::Token *t) {
    gen.endStmt();

    // std::cout<<"===============\n";
    prt(t, L"sem");
  }
  static void prt() {
    gen.add(dac::OpKind::Print);
    prt(NULL, L"prt");
  }
  static void doo() {
    gen.add(dac::OpKind::IfFalse);
    gen.ContextSetRef();
    gen.endStmt();
     prt(nullptr, L"do"); }
  static void rop(MIEC::Token *t) { 
    dac::OpKind kind;
    if(t->val==L"=")
    {
      kind=dac::OpKind::IsEq;
    } else if(t->val== L"<"){
      kind=dac::OpKind::IsLess;

    } else if(t->val== L">"){
      kind=dac::OpKind::IsGreater;

    } else if(t->val==L"<=") {
      kind=dac::OpKind::IsLeq;

    }else if (t->val==L">=") {
      kind=dac::OpKind::IsGtq;

    }else if (t->val==L"!=")
    {
      kind=dac::OpKind::IsNotEq;

    }else {
      throw "";
    //TODO: throw
    }
    gen.add(dac::OpKind::IsNotEq);
    prt(t, L"rop"); }
  // static
};
#endif //!__DAC_HELPER_H__