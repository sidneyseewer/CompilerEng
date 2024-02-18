#include "DacHelper.h"
#include "Scanner.h"
#include <cstddef>

void DacHelper::prt(MIEC::Token *t, wchar_t const *const s) {

#ifndef NDEBUG
  std::wcout << s << " ";
  if (t != nullptr)
    std::wcout << t->val;

  std::cout << std::endl;
#endif
}

void DacHelper::setErrorHandler(DacHelper::errorHandler e) { this->e = e; };
DacHelper::DacHelper(dac::Generator &gen, SymbolFactory &fac, SymbolTable &st)
    : gen(gen), factory(fac), symbolTable(st) {}
dac::Generator &&DacHelper::getGen() { return std::move(gen); }
void DacHelper::resetGen() {
  dac::Generator g{};
  gen = g;
}
void DacHelper::ass(MIEC::Token *t) {
  if (t != NULL) {
    auto tmp = symbolTable.Find(coco_string_create_char(t->val));
    gen.add(dac::OpKind::Assign, dac::SymbolOperand::create(tmp));
  }
  prt(t, L"ass");
}
void DacHelper::fac(MIEC::Token *t) {
  if (t != nullptr) {
    auto tmp = symbolTable.Find(coco_string_create_char(t->val));
    gen.add(dac::SymbolOperand::create(tmp));
  }
  prt(t, L"fac");
}
void DacHelper::fop(MIEC::Token *t) {
  if (t != nullptr) {
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
  }
  prt(t, L"fop");
}
void DacHelper::lpr() {
  gen.pushPr();
  prt(nullptr, L"lpr");
}
void DacHelper::rpr() {
  gen.popPr();
  prt(nullptr, L"rpr");
}
void DacHelper::top(MIEC::Token *t) {
  if (t != nullptr) {
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
  }
  prt(t, L"top");
}
void DacHelper::end() {
  gen.add(dac::OpKind::Exit);
  gen.endStmt();
  prt(NULL, L"end");
}
void DacHelper::wend() {
  gen.add(dac::OpKind::Jump, gen.ContextGetIndex());
  gen.ContextRef(1);
  gen.popContext();
  gen.endStmt();
  prt(NULL, L"wend");
}
void DacHelper::ifend() {
  gen.ContextRef();
  gen.popContext();
  gen.endStmt();
  prt(NULL, L"iend");
}
void DacHelper::wle() {
  gen.pushContext();
  gen.ContextSetIndex();
  prt(NULL, L"wle");
}
void DacHelper::els() {
  gen.add(dac::OpKind::Jump);
  gen.ContextRef(1);
  gen.ContextSetRef();
  prt(NULL, L"els");
}
void DacHelper::iff() {
  gen.pushContext();
  gen.ContextSetIndex();
  prt(NULL, L"iff");
}
void DacHelper::thn() {
  gen.add(dac::OpKind::IfFalse);
  gen.ContextSetRef();
  prt(NULL, L"thnx");
}
void DacHelper::sem() {
  gen.endStmt();

  // std::cout<<"===============\n";
  prt(NULL, L"sem");
}
void DacHelper::prt() {
  gen.add(dac::OpKind::Print);
  prt(NULL, L"prt");
}
void DacHelper::doo() {
  gen.add(dac::OpKind::IfFalse);
  gen.ContextSetRef();
  gen.endStmt();
  prt(nullptr, L"do");
}
void DacHelper::rop(MIEC::Token *t) {
  if (t != nullptr) {
    dac::OpKind kind;
    if (std::wcscmp(t->val, L"=") == 0) {
      kind = dac::OpKind::IsEq;
    } else if (std::wcscmp(t->val, L"<") == 0) {
      kind = dac::OpKind::IsLess;

    } else if (std::wcscmp(t->val, L">") == 0) {
      kind = dac::OpKind::IsGreater;

    } else if (std::wcscmp(t->val, L"<=") == 0) {
      kind = dac::OpKind::IsLeq;

    } else if (std::wcscmp(t->val, L">=") == 0) {
      kind = dac::OpKind::IsGtq;

    } else if (std::wcscmp(t->val, L"!=") == 0) {
      kind = dac::OpKind::IsNotEq;

    } else {
      e(L"unsupported operation");
    }
    gen.add(kind);
  }
  prt(t, L"rop");
}
void DacHelper::verifyVarSymbol(MIEC::Token*t)
{
  if(t!=nullptr&&symbolTable.Find(coco_string_create_char(t->val))!=nullptr)
  {

  }
  else {
    e(L"unknown variable");
  }
}
Symbol::ptr DacHelper::addConstSymbol(std::string const &name) {
  auto x = symbolTable.Find(name);
  if (x == nullptr) {
    x = factory.CreateConst(name);
    symbolTable.Add(x);
  }
  return x;
}
Symbol::ptr DacHelper::addVarSymbol(std::string const &name) {
  auto x = symbolTable.Find(name);
  if (x == nullptr) {
    x = factory.CreateVar(name);
    symbolTable.Add(x);
  } else {
    e(L"double declaratuion variable ");
  }
  return x;
}
Symbol::ptr DacHelper::addTypeSymbol(std::string const &name) {
  auto x = symbolTable.Find(name);
  if (x == nullptr) {
    x = factory.CreateType(name);
    symbolTable.Add(x);
  }
  return x;
}