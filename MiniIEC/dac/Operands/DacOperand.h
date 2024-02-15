#ifndef __DAC_DAC_OPERAND_H__
#define __DAC_DAC_OPERAND_H__

#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {

class Entry;

class DacOperand:public Operand{
Entry::ptr mResult=nullptr;
Entry::ptr mJump=nullptr;
void x()override{} 
public:
Entry::ptr getResult(){return mResult;}
Entry::ptr getJump(){return mJump;}
Entry::ptr get(){return mResult==nullptr?mJump:mResult;}
bool isResult(){return mResult!=nullptr;}
bool isJump(){return mJump!=nullptr;}
    enum Type{Result,Jump};
    DacOperand(Entry::ptr entr,Type tmp):mJump(nullptr),mResult(nullptr){
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
    static DacOperand::ptr createResult(Entry::ptr e){return std::make_shared<DacOperand>(e,Result);};
    static DacOperand::ptr createJump(Entry::ptr e){return std::make_shared<DacOperand>(e,Jump);};
};
}

#endif //!__DAC_DAC_OPERAND_H__