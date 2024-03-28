/**
 * @file helper.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "helper.h"
#include "dac/Entry.h"

std::wstring toString(dac::Operand::ptr  const&p){

std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  auto sop = dac::extract<dac::SymbolOperand>(p);
  auto dop = dac::extract<dac::DacOperand>(p);
  if (sop != nullptr) {
    return converter.from_bytes((sop->get()->GetName()));
  }
  if (dop != nullptr) {
    std::string s = "";
    if (dop->isJump())
      s += "j";
    if (dop->isResult())
      s += "r";
    dac::Entry::ptr x=dop->get();
    return converter.from_bytes(std::format(" *{1}", s,x->getPosition()));
  }
  return L"";
}