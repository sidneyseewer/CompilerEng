
#include "dac/Entry.h"
#include "dac/Operands/Operand.h"
#include "lib/helper.h"
#include <vector>
class RegisterAdmin {
private:
  const size_t regCount;
  std::vector<dac::Operand::ptr> registers{};

public:
  using RegNr = size_t;
  RegisterAdmin(size_t const regCount);
  RegNr GetRegister();

  RegNr GetRegister(dac::Operand::ptr const &op);
  bool hasRegister(dac::Operand::ptr const &op);
  void FreeRegister(RegNr const nr);
  RegNr AssignRegister(RegNr const nr, dac::Entry::ptr const &entry);
  RegNr AssignRegister(RegNr const nr, Symbol::ptr const &symbol);
};
