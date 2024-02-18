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
#include <cwchar>
#include <format>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
class dach {
  static void prt(MIEC::Token *t, wchar_t const * const s) {

    #ifndef NDEBUG
    std::wcout << s << " ";
    if (t != nullptr)
      std::wcout << t->val;

    std::cout << std::endl;
    #endif
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
  
  static dac::Generator gen;

public:
static dac::Generator&& getGen(){
  return std::move(gen);
}
static void resetGen(){
  dac::Generator g{};
  gen=g;
}
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
      throw "unsuported fop"; // TODO:
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
      throw "unsupported top"; // TODO:
    }
    gen.addt(kind);
    prt(t, L"top"); }
  static void end() {
    gen.add(dac::OpKind::Exit);
    gen.endStmt();
    prt(NULL, L"end");
  }static void wend() {
    gen.add(dac::OpKind::Jump,gen.ContextGetIndex());
    gen.ContextRef();
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"wend");
  }static void ifend() {
    gen.ContextRef();
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"iend");
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
  static void sem() {
    gen.endStmt();

    // std::cout<<"===============\n";
    prt(NULL,L"sem");
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
    if(std::wcscmp(t->val,L"=")==0)
    {
      kind=dac::OpKind::IsEq;
    } else if(std::wcscmp(t->val,L"<")==0){
      kind=dac::OpKind::IsLess;

    } else if(std::wcscmp(t->val,L">")==0){
      kind=dac::OpKind::IsGreater;

    } else if(std::wcscmp(t->val,L"<=")==0) {
      kind=dac::OpKind::IsLeq;

    }else if (std::wcscmp(t->val,L"<=")==0) {
      kind=dac::OpKind::IsGtq;

    }else if (std::wcscmp(t->val,L"!=")==0)
    {
      kind=dac::OpKind::IsNotEq;

    }else {
      throw "unsupported rop";
    //TODO: throw
    }
    gen.add(kind);
    prt(t, L"rop"); }
  // static
};
#endif //!__DAC_HELPER_H__