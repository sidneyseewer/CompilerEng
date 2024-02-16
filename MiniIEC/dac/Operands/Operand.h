#ifndef __DAC_OPERAND_H__
#define __DAC_OPERAND_H__

#include "lib/concepts.h"
#include <memory>

namespace dac {

class Operand{
public:
virtual void x()=0;
using ptr=std::shared_ptr<Operand>;
};

template <Derived<Operand> F>
F* extract(std::shared_ptr<Operand>o){
    if(o!=nullptr) return dynamic_cast<F*>(o.get());return nullptr;
}
}
#endif //!__DAC_OPERAND_H__