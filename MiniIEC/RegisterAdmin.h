
#include <vector>
#include "dac/Operands/Operand.h"
#include "lib/helper.h"
#include "dac/Entry.h"
class RegisterAdmin {
private:
  const size_t regCount;
  std::vector<dac::Operand::ptr> registers{};

public:
  using RegNr = size_t;
  RegisterAdmin(size_t const regCount):regCount(regCount){registers.resize(regCount);}
  RegNr GetRegister() {
    for (RegNr i = 0; i < registers.size(); i++) {
      if (registers.at(i) == nullptr)
        return i + 1;
    }
    throw "no free register available";
  }


  RegNr GetRegister(dac::Operand::ptr op) {
    for (RegNr i = 0; i < registers.size(); i++) {
      auto opt =registers.at(i);
      if (Compare_operand_pointer<std::equal_to<void*>>(opt, op))
        return i + 1;
    }
    throw "not found";
  }
  bool hasRegister(dac::Operand::ptr op) {
    for (RegNr i = 0; i < registers.size(); i++) {
      if (Compare_operand_pointer<std::equal_to<void *>>(op, registers[i]))
        return true;
    }
    return false;
  }
  void FreeRegister(RegNr const nr) {
    auto index = nr - 1;
    if (index < registers.size()) {
      registers[index] = nullptr;
    } else {
      throw "Register out of range";
    }
  }
  RegNr AssignRegister(RegNr const nr, dac::Entry::ptr entry) {
    auto index = nr - 1;
    if (index < registers.size()) {
      registers[index] = dac::DacOperand::createResult(entry);
    } else {
      throw "Register out of range";
    }
    return index + 1;
  }
  RegNr AssignRegister(RegNr const nr, Symbol::ptr symbol) {
    auto index = nr - 1;
    if (index < registers.size()) {
      registers[index] = dac::SymbolOperand::create(symbol);
    } else {
      throw "Register out of range";
    }
    return index + 1;
  }
};
