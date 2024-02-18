#ifndef __DAC_OPERAND_H__
#define __DAC_OPERAND_H__

#include "Object.h"
#include "lib/concepts.h"
#include <memory>

namespace dac {

class Operand:public Object{
protected:
virtual void x()=0;
public:
using ptr=std::shared_ptr<Operand>;
};

template <Derived<Operand> F>
F* extract(std::shared_ptr<Operand> const&o){
    if(o!=nullptr) return dynamic_cast<F*>(o.get());return nullptr;
}
}
#endif //!__DAC_OPERAND_H__