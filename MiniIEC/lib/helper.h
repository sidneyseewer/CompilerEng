#ifndef __HELPER_H__
#define __HELPER_H__

#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <algorithm>
#include <functional>
#include <memory>

template <class UnaryPredicate>
bool Compare_operand_pointer(dac::Operand::ptr const& a,dac::Operand::ptr const& b)
{
    UnaryPredicate p{};
    auto a1=dac::extract<dac::SymbolOperand>(a);
    auto b1=dac::extract<dac::SymbolOperand>(b);
    auto a2=dac::extract<dac::DacOperand>(a);
    auto b2=dac::extract<dac::DacOperand>(b);
    if(a1!=nullptr&&b1!=nullptr)
    {
        return p(a1->get().get(),b1->get().get());
    } 
    if(a2!=nullptr&&b2!=nullptr)
    {
        return p(a2->get().get(),b2->get().get());
    }
    if(p(a.get(),b.get())) return true;
    return false;
}
template<class UP>
struct OperandPointer{
    constexpr bool operator()(dac::Operand::ptr const& a,dac::Operand::ptr const& b) const
    {
        return Compare_operand_pointer<UP>(a,b);
    }

};
inline bool operator==(dac::Operand::ptr const& a,dac::Operand::ptr const& b){
    return Compare_operand_pointer<std::equal_to<void*>>(a, b);
}
inline bool operator<(dac::Operand::ptr const& a,dac::Operand::ptr const& b){
    return Compare_operand_pointer<std::less<void*>>(a, b);
}
#endif //!__HELPER_H__