/**
 * @file RegisterAdmin.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief register admin implementation
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "RegisterAdmin.h"

RegisterAdmin::RegisterAdmin(size_t const regCount) : regCount(regCount) {
  registers.resize(regCount);
}
RegisterAdmin::RegNr RegisterAdmin::GetRegister() {
  for (RegisterAdmin::RegNr i = 0; i < registers.size(); i++) {
    if (registers.at(i) == nullptr)
      return i + 1;
  }
  throw "no free register available";
}

RegisterAdmin::RegNr RegisterAdmin::GetRegister(dac::Operand::ptr const &op) {
  for (RegNr i = 0; i < registers.size(); i++) {
    auto opt = registers.at(i);
    if (Compare_operand_pointer<std::equal_to<void *>>(opt, op))
      return i + 1;
  }
  throw "not found";
}
bool RegisterAdmin::hasRegister(dac::Operand::ptr const &op) {
  for (RegNr i = 0; i < registers.size(); i++) {
    if (Compare_operand_pointer<std::equal_to<void *>>(op, registers[i]))
      return true;
  }
  return false;
}
void RegisterAdmin::FreeRegister(RegNr const nr) {
  auto index = nr - 1;
  if (index < registers.size()) {
    registers[index] = nullptr;
  }
}
RegisterAdmin::RegNr
RegisterAdmin::AssignRegister(RegNr const nr, dac::Entry::ptr const &entry) {
  auto index = nr - 1;
  if (index < registers.size()) {
    registers[index] = dac::DacOperand::createResult(entry);
  } else {
    throw "Register out of range";
  }
  return index + 1;
}
RegisterAdmin::RegNr RegisterAdmin::AssignRegister(RegNr const nr,
                                                   Symbol::ptr const &symbol) {
  auto index = nr - 1;
  if (index < registers.size()) {
    registers[index] = dac::SymbolOperand::create(symbol);
  } else {
    throw "Register out of range";
  }
  return index + 1;
}