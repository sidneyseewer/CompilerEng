
#ifndef __NEXT_USE_CALC_H__
#define __NEXT_USE_CALC_H__

#include "Symbols/Symbol.h"
#include "dac/Entry.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include "lib/helper.h"
#include <cstddef>
#include <optional>
#include <sys/types.h>
#include <vector>

class NCC{
  public:
  using key_type=dac::Operand::ptr;
  using value_type=std::optional<size_t>;
  private:
  std::vector<std::pair<key_type,value_type>>container;
  public:

  void set(key_type k,value_type v){
    OperandPointer<std::less<void*>> op{};
    for(auto a:container)
    {
      if(op(a.first,k))
      {
        a.second=v;
        return;
      }
    }
    container.emplace_back(k,v);
  }
  // bool hasKey(key_type k);
  // value_type get(key_type k){}
  auto begin(){return container.begin();}
  auto end(){return container.end();}
};

class NextUseCalc{
  using NextUsage_container = std::map<dac::Operand::ptr, std::optional<size_t>,OperandPointer<std::less<void*>>>;
  NextUsage_container lu{};
  void addOP(auto ps,size_t i){

    auto a =extract<dac::SymbolOperand>(ps);
    dac::DacOperand* b =extract<dac::DacOperand>(ps);
    if(a!=nullptr||(b!=nullptr&&b->isResult()))
      lu[ps]=i;
  }
    public:
    template<class Itr>
void Calc(Itr const& begin,Itr const& end){
 
  constexpr auto set=NextUsage_container::mapped_type{};
  for(int i=end-begin-1;i>=0;i--)
  {
    dac::Entry::ptr e=*(begin+i);
    dac::OpKind op= e->getKind();
    for (auto s : lu) {
      if(s.second.has_value())
        e->addnextUsed(s.first, s.second.value());
    }
    switch (op) {

    case dac::Add:
    case dac::Sub:
    case dac::Mult:
    case dac::Div:
    // instructions with result stored in register
    lu[dac::DacOperand::createResult(e)]=set;
    break;
    case dac::Assign:
    // instructions with result sored im memory

    lu[e->getFirst()]=set;
    break;
    case dac::IsEq:
    case dac::IsLeq:
    case dac::IsGtq:
    case dac::IsNotEq:
    case dac::IsLess:
    case dac::IsGreater:
    case dac::Jump:
    case dac::IfFalse:
    case dac::Print:
    case dac::Exit:
      break;
    }
    if(op!=dac::Assign)
      addOP(e->getFirst(),i);
    addOP(e->getSecond(),i);

  }

  // // calculate next usage
  // using NextUsage_container = std::map<dac::Operand::ptr, std::optional<size_t>,OperandPointer<std::less<void*>>>;
  // NextUsage_container lu;
  // constexpr auto set=NextUsage_container::mapped_type{};

  // for (int i = end-begin - 1; i >= 0; i--) {
  //   auto itr = lu.begin();
  //   auto e = (begin + i);
    
  //   if (e->get()->getFirst() != nullptr) {
  //       lu[e->get()->getFirst()] = i;
  //     }
  //   auto ps = e->get()->getSecond();
  //   if (ps != nullptr) {
  //     // auto s = dac::extract<dac::SymbolOperand>(ps);
  //     // if (s != nullptr) {
  //     lu[ps] = i;
  //     // }
  //   }
  //   for (auto s : lu) {
  //     if(s.second.has_value())
  //       e->get()->addnextUsed(s.first, s.second.value());
  //   }
  //   if (e->get()->getKind() == dac::Assign) {

  //     if (e->get()->getFirst() != nullptr) {
  //       lu[e->get()->getFirst()]=set;
  //       // lu.erase(e->get()->getFirst());
  //     }
  //   } else {
  //     lu[dac::DacOperand::createResult(*e)]=set;
  //     // auto f = dac::extract<dac::SymbolOperand>(e->get()->getFirst());
      
  //   }
  // }
}
};

#endif //!__NEXT_USE_CALC_H__