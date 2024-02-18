#ifndef __DAC_GENERATOR_H__
#define __DAC_GENERATOR_H__

#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/Operand.h"
#include <cstddef>
#include <vector>
namespace dac {

class Generator{
public:
    void add(OpKind index,Operand::ptr first);
    void add(OpKind kind,size_t index);
    void add(OpKind kind);
    void addt(OpKind kind);
    void addf(OpKind kind);
    void add(Operand::ptr op);
    void pushPr();
    void popPr();
    void pushContext();
    void popContext();
    void ContextSetIndex();
    size_t ContextGetIndex();
    void ContextSetRef();
    void ContextRef();
    void endStmt();
    void Print(std::ostream);
    std::vector<Entry::ptr> getCode();
    /**
    sets the position member of each entry to the index in the code array
    */
    void updateIndex();
    Generator(){
        auto tmp=dac::Entry::create(OpKind::Exit);
        statementContext.emplace_back(tmp,tmp,tmp);
    }
    auto cend()const{return code.cend();};
    auto cbegin()const{return code.cbegin();};
    auto end(){return code.end();};
    auto begin(){return code.begin();};
    size_t size()const{return code.size();}
    void add(Entry::ptr a);
    Entry::ptr operator[](size_t index){return code[index];}
    void updateJumpRefs();
    private:
    struct FlowContext{
        Entry::ptr ref;
        size_t index;
    };
    struct StatementContext{
        Entry::ptr root;
        Entry::ptr A;
        Entry::ptr B;
        Entry::ptr C;
    };
    struct JumpRef{
        Entry::ptr entry;
        size_t destination;
    };

    std::vector<Entry::ptr> code{};
    std::vector<FlowContext> flowContext{};
    std::vector<StatementContext> statementContext{};
    std::vector<JumpRef> jumpRefs{};
};
}
#endif //!__DAC_GENERATOR_H__