/**
 * @file Operand.h
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief Base class for all operand types
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __DAC_OPERAND_H__
#define __DAC_OPERAND_H__

#include "Object.h"
#include "lib/concepts.h"
#include <memory>

namespace dac {
/**
 * @brief Base class for all operand types
 * 
 */
class Operand:public Object{
protected:
virtual void x()=0;
public:
using ptr=std::shared_ptr<Operand>;
};

/**
 * @brief converts o to Pointer of F
 * 
 * @tparam F 
 * @param o 
 * @return F* 
 */
template <Derived<Operand> F>
F* extract(std::shared_ptr<Operand> const&o){
    if(o!=nullptr) return dynamic_cast<F*>(o.get());return nullptr;
}
}
#endif //!__DAC_OPERAND_H__