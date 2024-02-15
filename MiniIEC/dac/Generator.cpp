#include "Generator.h"
#include "dac/Entry.h"
#include "dac/OpKind.h"
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
  tmp->setSecond(root->getFirst());
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
  if (parent->getKind() == OpKind::Exit) {
    tmp->setFirst(parent->getSecond());
    parent->setSecond(DacOperand::createResult(tmp));
  } else {
    tmp->setFirst(parent->getSecond());
    parent->setSecond(DacOperand::createResult(tmp));
  }
  statementContext.back().A = tmp;
  statementContext.back().B = tmp;
}
void Generator::addf(OpKind kind) {

  auto tmp = dac::Entry::create(kind);
  auto parent = statementContext.back().B;
  if (parent->getKind() == OpKind::Exit) {
    tmp->setFirst(parent->getSecond());
    parent->setSecond(DacOperand::createResult(tmp));
  } else {
    tmp->setFirst(parent->getSecond());
    parent->setSecond(DacOperand::createResult(tmp));
  }
  statementContext.back().A = tmp;
}
void Generator::add(Operand::ptr op) {
  statementContext.back().A->setSecond(op);
}
void Generator::pushPr() {
  auto tmp = dac::Entry::create(OpKind::Exit);
  statementContext.emplace_back(tmp, tmp, tmp, tmp);
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

void treeToVec(std::vector<Entry::ptr> &&v, Entry::ptr const &e) {
  DacOperand *ref;
  v.push_back(e);
  if (e != nullptr) {
    ref = dynamic_cast<DacOperand *>(e->getFirst().get());
    if (ref != nullptr) {
      treeToVec(std::move(v), ref->get());
    }
    ref = dynamic_cast<DacOperand *>(e->getSecond().get());
    if (ref != nullptr) {
      treeToVec(std::move(v), ref->get());
    }
  }
}
void Generator::endStmt() {
  std::vector<Entry::ptr> stmcode;
  auto node = statementContext.back().root;
  auto ref = dynamic_cast<DacOperand *>(node->getFirst().get());
  if(ref!=nullptr)
    treeToVec(std::move(stmcode),ref->get());
  std::reverse_copy(stmcode.cbegin(), stmcode.cend(), std::back_inserter(code));
  statementContext.clear();
  pushPr();
}

void Generator::updateIndex(){
  for(size_t i=0;i<code.size();i++)
  {
    code[i]->setPosition(i);
  }
}
// void Generator::Print(std::ostream ostream) {
//   if (ostream.good()) {
//     for (auto itr = mEntries.cbegin(); itr != mEntries.cend(); itr++) {
//       ostream << itr->get() << std::endl;
//     }
//   }
// }