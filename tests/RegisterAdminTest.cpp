#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include "dac/Operands/Operand.h"
#include <catch2/catch_test_macros.hpp>
#include <RegisterAdmin.h>
#include <dac/Entry.h>
TEST_CASE( "Simpel" ) {
    RegisterAdmin uut{12};
    auto a =dac::DacOperand::createResult(dac::Entry::create(dac::OpKind::Add));
    auto b =dac::DacOperand::createResult(dac::Entry::create(dac::OpKind::Add));
    auto c= dac::DacOperand::createResult(dac::Entry::create(dac::OpKind::Add));
    uut.AssignRegister(1,a->get());
    uut.AssignRegister(2,b->get());
    REQUIRE(uut.hasRegister(a));
    REQUIRE(uut.hasRegister(b));
    REQUIRE_FALSE(uut.hasRegister(c));
    REQUIRE(uut.GetRegister(a)==1);
    REQUIRE(uut.GetRegister(b)==2);
    REQUIRE_THROWS([&](){uut.GetRegister(c);}());
    REQUIRE(uut.GetRegister()==3);
    uut.FreeRegister(1);
    REQUIRE_FALSE(uut.hasRegister(a));
    REQUIRE(uut.GetRegister()==1);
}

TEST_CASE("S")
{
    
}