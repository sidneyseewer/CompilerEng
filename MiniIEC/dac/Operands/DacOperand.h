#ifndef __DAC_DAC_OPERAND_H__
#define __DAC_DAC_OPERAND_H__

#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class Entry;
using Entry_ptr=std::shared_ptr<Entry>;

class DacOperand:public Operand{
Entry_ptr mResult=nullptr;
Entry_ptr mJump=nullptr;
public:
using ptr=std::shared_ptr<DacOperand>;
void x()override{}
Entry_ptr getResult(){return mResult;}
Entry_ptr getJump(){return mJump;}
Entry_ptr get(){return mResult==nullptr?mJump:mResult;}
bool isResult(){return mResult!=nullptr;}
bool isJump(){return mJump!=nullptr;}
    enum Type{Result,Jump};
    DacOperand(Entry_ptr entr,Type tmp):mJump(nullptr),mResult(nullptr){
        switch (tmp) {
            case Result:
                mResult=entr;
                break;
            case Jump:
                mJump=entr;
            break;
            default:
                throw "enum out of range";
        }
    }
    // using ptr = std::shared_ptr<DacOperand>;
    static DacOperand::ptr createResult(Entry_ptr e){return std::make_shared<DacOperand>(e,Result);};
    static DacOperand::ptr createJump(Entry_ptr e){return std::make_shared<DacOperand>(e,Jump);};
    static bool is(Operand::ptr o){if(o!=nullptr) return dac::extract<DacOperand>(o)!=nullptr;return false;}
};
}

#endif //!__DAC_DAC_OPERAND_H__