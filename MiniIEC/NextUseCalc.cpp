#include "NextUseCalc.h"

//   void NCC::set(key_type k, value_type v) {
//     OperandPointer<std::less<void *>> op{};
//     for (auto a : container) {
//       if (op(a.first, k)) {
//         a.second = v;
//         return;
//       }
//     }
//     container.emplace_back(k, v);
//   }
//   // bool hasKey(key_type k);
//   // value_type get(key_type k){}
//   NCC::Container::iterator NCC::begin() { return container.begin(); }
//   NCC::Container::iterator NCC::end() { return container.end(); }

void NextUseCalc::addOP(dac::Operand::ptr const &ps, size_t const &i) {

  auto a = extract<dac::SymbolOperand>(ps);
  dac::DacOperand *b = extract<dac::DacOperand>(ps);
  if (a != nullptr || (b != nullptr && b->isResult()))
    lu[ps] = i;
}
