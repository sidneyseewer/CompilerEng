#include "helper.h"
#include "dac/Entry.h"

std::string toString(dac::Operand::ptr p){
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
    dac::Entry::ptr x=dop->get();
    return std::format(" *{1}", s,x->getPosition());
  }
  return "";
}