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
using errorHandler=std::function<void(wchar_t const*const)>;
private:
  void prt(MIEC::Token *t, wchar_t const * const s) {

    #ifndef NDEBUG
    std::wcout << s << " ";
    if (t != nullptr)
      std::wcout << t->val;

    std::cout << std::endl;
    #endif
  }

  void print(dac::Entry::ptr e)
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
  void print (dac::Operand::ptr e){
    
  }
  
  dac::Generator &gen;
  SymbolFactory&factory;
  SymbolTable&symbolTable;
  errorHandler e;
public:
void setErrorHandler(errorHandler e){this->e=e;};
  DacHelper(dac::Generator &gen,SymbolFactory &fac=SymbolFactory::GetInstance(),SymbolTable&st=SymbolTable::GetInstance()):gen(gen),factory(fac),symbolTable(st){}
dac::Generator&& getGen(){
  return std::move(gen);
}
void resetGen(){
  dac::Generator g{};
  gen=g;
}
  void ass(MIEC::Token *t) {
    auto tmp = symbolTable.Find(coco_string_create_char(t->val));
    gen.add(dac::OpKind::Assign,dac::SymbolOperand::create(tmp));
    prt(t, L"ass");
  }
  void fac(MIEC::Token *t) {
    auto tmp = symbolTable.Find(coco_string_create_char(t->val));
    gen.add(dac::SymbolOperand::create(tmp));
    prt(t, L"fac");
  }
  void fop(MIEC::Token *t) {
    dac::OpKind kind;
    switch (*t->val) {
    case L'*':
      kind = dac::OpKind::Mult;
      break;
    case L'/':
      kind = dac::OpKind::Div;
      break;
    default:
      e(L"unsupported operation");
    }
    gen.addf(kind);
    prt(t, L"fop");
  }
  void lpr() {
    gen.pushPr();
    prt(nullptr, L"lpr"); }
  void rpr() { 
    gen.popPr();
    prt(nullptr, L"rpr"); }
  void top(MIEC::Token *t) { 
    dac::OpKind kind;
    switch (*t->val) {
    case L'+':
      kind = dac::OpKind::Add;
      break;
    case L'-':
      kind = dac::OpKind::Sub;
      break;
    default:
    e(L"unsopported operation");
    }
    gen.addt(kind);
    prt(t, L"top"); }
  void end() {
    gen.add(dac::OpKind::Exit);
    gen.endStmt();
    prt(NULL, L"end");
  }void wend() {
    gen.add(dac::OpKind::Jump,gen.ContextGetIndex());
    gen.ContextRef(1);
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"wend");
  }void ifend() {
    gen.ContextRef();
    gen.popContext();
    gen.endStmt();
    prt(NULL, L"iend");
  }
  void wle() {
    gen.pushContext();
    gen.ContextSetIndex();
    prt(NULL, L"wle");
  }
  void els() { 
    gen.add(dac::OpKind::Jump);
    gen.ContextRef(1);
    gen.ContextSetRef();
    prt(NULL, L"els"); }
  void iff() {
    gen.pushContext();
    gen.ContextSetIndex();
    prt(NULL, L"iff");
  }
  void thn() {
    gen.add(dac::OpKind::IfFalse);
    gen.ContextSetRef();
    prt(NULL, L"thnx"); }
  void sem() {
    gen.endStmt();

    // std::cout<<"===============\n";
    prt(NULL,L"sem");
  }
  void prt() {
    gen.add(dac::OpKind::Print);
    prt(NULL, L"prt");
  }
  void doo() {
    gen.add(dac::OpKind::IfFalse);
    gen.ContextSetRef();
    gen.endStmt();
     prt(nullptr, L"do"); }
  void rop(MIEC::Token *t) { 
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

    }else if (std::wcscmp(t->val,L">=")==0) {
      kind=dac::OpKind::IsGtq;

    }else if (std::wcscmp(t->val,L"!=")==0)
    {
      kind=dac::OpKind::IsNotEq;

    }else {
      e(L"unsupported operation");
    }
    gen.add(kind);
    prt(t, L"rop"); }
  
  Symbol::ptr addConstSymbol(std::string name) {
    auto x = symbolTable.Find(name);
    if (x == nullptr) {
        x=factory.CreateConst(name);
        symbolTable.Add(x);
    }
    return x;
  }
  Symbol::ptr addVarSymbol(std::string name) {
    auto x = symbolTable.Find(name);
    if (x == nullptr) {
        x=factory.CreateVar(name);
        symbolTable.Add(x);
    }
    else {
      e(L"double declaratuion variable ");
    }
    return x;
  }
  Symbol::ptr addTypeSymbol(std::string name) {
    auto x = symbolTable.Find(name);
    if (x == nullptr) {
        x=factory.CreateType(name);
        symbolTable.Add(x);
    }
    return x;
  }
};
#endif //!__DAC_HELPER_H__