#include "Generator.h"
#include "dac/Entry.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "iostream"
#include "ostream"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
using namespace dac;

void Generator::add(Entry::ptr tmp) {
  auto root = statementContext.back().root;
  tmp->setFirst(root->getFirst());
  root->setFirst(DacOperand::createResult(tmp));
  statementContext.back().A = tmp;
  statementContext.back().B = tmp;
  statementContext.back().C = tmp;
}
void Generator::add(OpKind kind, Operand::ptr first) {
  add(dac::Entry::create(kind, first));
}
void Generator::add(OpKind kind, size_t index) {
  if (index < code.size()) {
    add(Entry::create(kind, DacOperand::createJump(code[index])));
  } else {
    throw "AKEsoe";
    // TODO
  }
}
void Generator::add(OpKind kind) { add(dac::Entry::create(kind)); }
void Generator::addt(OpKind kind) {
  auto tmp = dac::Entry::create(kind);
  auto parent = statementContext.back().C;
  tmp->setFirst(parent->getFirst());
  parent->setFirst(DacOperand::createResult(tmp));
  statementContext.back().A = tmp;
  statementContext.back().B = tmp;
}
void Generator::addf(OpKind kind) {

  auto tmp = dac::Entry::create(kind);
  auto parent = statementContext.back().B;
  tmp->setFirst(parent->getFirst());
  parent->setFirst(DacOperand::createResult(tmp));
  statementContext.back().A = tmp;
}
void Generator::add(Operand::ptr op) {
  statementContext.back().A->setSecond(op);
}
void Generator::pushPr() {
  auto tmp = dac::Entry::create(OpKind::Exit);
  statementContext.emplace_back(tmp, tmp, tmp,tmp);
}
void Generator::popPr() {
  auto tmp = statementContext.back();
  statementContext.pop_back();
  statementContext.back().A->setSecond(tmp.root->getSecond());
}
void Generator::pushContext() { flowContext.push_back({}); }
void Generator::popContext() { flowContext.pop_back(); }
void Generator::ContextSetIndex() { flowContext.back().index = code.size(); }
size_t Generator::ContextGetIndex() { return flowContext.back().index; }
void Generator::ContextSetRef() {
  flowContext.back().ref = statementContext.back().A;
}
void Generator::ContextRef() {
  jumpRefs.emplace_back(flowContext.back().ref, code.size());
}

Entry::ptr help(Entry::ptr e, bool b) {
  DacOperand *ref;

  if (e != nullptr) {
    Operand::ptr x;
    if (b) {
      x=e->getFirst();
    } else {
      x=e->getSecond();
    }
    Operand* y=x.get();
    ref = dynamic_cast<DacOperand *>(y);
  }
  if (ref != nullptr) {
    return ref->get();
  }
  return nullptr;
}
void Generator::endStmt() {
  std::vector<Entry::ptr> stmcode;
  auto node = statementContext.back().root;
  std::vector<Entry::ptr> stack{};
  do {
    if(node!=nullptr)
    {
    do {
      stack.push_back(node);
      node = help(node, true);
    } while (node != nullptr);
    }
    auto tmp = stack.back();
    stack.pop_back();
    // std::cout << tmp->getKind() << std::endl;
    stmcode.push_back(tmp);
    node = help(tmp, false);
  } while (node == nullptr && stack.size() != 0);
  std::reverse_copy(stmcode.cbegin(),stmcode.cend(),std::back_inserter(code));
}

// void Generator::Print(std::ostream ostream) {
//   if (ostream.good()) {
//     for (auto itr = mEntries.cbegin(); itr != mEntries.cend(); itr++) {
//       ostream << itr->get() << std::endl;
//     }
//   }
// }