#include "Scanner.h"
#include "dac/Generator.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include "dac/Operands/SymbolOperand.h"
#include <catch2/catch_test_macros.hpp>
#include <DacHelper.h>
#include <cstdint>
#include <cstdlib>
#include <vector>

MIEC::Token createToken(wchar_t * v)
{
    
    MIEC::Token t;
    t.val=v;
    return  t;
}
class TokenGen{
    std::vector<MIEC::Token*> tokens;
  public:
  MIEC::Token*create(wchar_t * v)
  {
    MIEC::Token*t=(MIEC::Token*)malloc(sizeof(MIEC::Token));
    t->val=v;
    tokens.push_back(t);
    return tokens.back();
  }  
  ~TokenGen(){
    for(auto a:tokens)
    {
        delete a;
    }
  }
};
TEST_CASE("DacHelper If")
{
    dac::Generator dacg{};
    DacHelper dach{dacg};
    TokenGen g{};
    dach.iff();
    dach.fac(g.create(L"a"));
    dach.rop(g.create(L"<"));
    dach.fac(g.create(L"b"));
    dach.thn();
    dach.prt();
    dach.fac(g.create(L"a"));
    dach.sem();
    dach.els();
    dach.prt();
    dach.fac(g.create(L"b"));
    dach.sem();
    dach.ifend();
    dach.end();
    auto code=dach.getGen().getCode();

    REQUIRE(code[0]->getKind()==dac::OpKind::IsLess);
    REQUIRE(dac::extract<dac::SymbolOperand>(code[0]->getFirst())->get()->GetName()=="a");
    REQUIRE(dac::extract<dac::SymbolOperand>(code[0]->getSecond())->get()->GetName()=="b");

    REQUIRE(code[1]->getKind()==dac::OpKind::IfFalse);
    REQUIRE(dac::extract<dac::DacOperand>(code[0]->getFirst())->getResult()==code[0]);
    REQUIRE(dac::extract<dac::DacOperand>(code[0]->getSecond())->getJump()==code[4]);
}