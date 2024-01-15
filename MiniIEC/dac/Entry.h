#ifndef __DAC_ENTRY_H__
#define __DAC_ENTRY_H__

#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <memory>
namespace dac {
class Entry{
    private:
    OpKind mOpKind;
    Operand::ptr mFirst;
    Operand::ptr mSec;
    public:
    Entry(OpKind k,Operand::ptr first,Operand::ptr second):mOpKind(k),mFirst(first),mSec(second){}
    Entry(OpKind k,Operand::ptr first):mOpKind(k),mFirst(first),mSec(nullptr){}
    Entry(OpKind k):mOpKind(k),mFirst(nullptr),mSec(nullptr){}
    using ptr=std::shared_ptr<Entry>;
    void setSecond(Operand::ptr op){mSec=op;};
    void setFirst(Operand::ptr op){mFirst=op;};
    Operand::ptr& getFirst(){return mFirst;}
    Operand::ptr& getSecond(){return mSec;}
    OpKind getKind(){return mOpKind ;}
    static Entry::ptr create(OpKind k,Operand::ptr first,Operand::ptr second){return std::make_shared<Entry>(k,first,second);}
    static Entry::ptr create(OpKind k,Operand::ptr first){return std::make_shared<Entry>(k,first);}
    static Entry::ptr create(OpKind k){return std::make_shared<Entry>(k);}
};
}


#endif //!__DAC_ENTRY_H__