#ifndef __DAC_OPERAND_H__
#define __DAC_OPERAND_H__

#include <memory>
namespace dac {

class Operand{
public:
virtual void x()=0;
using ptr=std::shared_ptr<Operand>;
};
}
#endif //!__DAC_OPERAND_H__