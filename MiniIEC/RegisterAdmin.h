/**
 * @file RegisterAdmin.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief register admin
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "dac/Entry.h"
#include "dac/Operands/Operand.h"
#include "lib/helper.h"
#include <vector>
/**
 * @brief manages which registers contain what variable
 * 
 */
class RegisterAdmin {
private:
  const size_t regCount;
  std::vector<dac::Operand::ptr> registers{};

public:
  using RegNr = size_t;
  RegisterAdmin(size_t const regCount);
  /**
   * @brief get first free register
   * 
   * @return RegNr 
   */
  RegNr GetRegister();
/**
 * @brief get register of op
 * 
 * @param op 
 * @return RegNr 
 */
  RegNr GetRegister(dac::Operand::ptr const &op);
  /**
   * @brief check if value of op is stored in registers
   * 
   * @param op 
   * @return true 
   * @return false 
   */
  bool hasRegister(dac::Operand::ptr const &op);
  /**
   * @brief free a register
   * 
   * @param nr 
   */
  void FreeRegister(RegNr const nr);
  /**
   * @brief assign register nr to entry
   * 
   * @param nr 
   * @param entry 
   * @return RegNr 
   */
  RegNr AssignRegister(RegNr const nr, dac::Entry::ptr const &entry);
  /**
   * @brief assign register nr to Symbol
   * 
   * @param nr 
   * @param symbol 
   * @return RegNr 
   */
  RegNr AssignRegister(RegNr const nr, Symbol::ptr const &symbol);
};
