
#include "dac/Entry.h"
#include "dac/OpKind.h"
#include "dac/Operands/DacOperand.h"
#include <lib/helper.h>
#include <catch2/catch_test_macros.hpp>
#include <functional>

TEST_CASE("Compare_Operand_Pointer")
{
    auto e1=dac::Entry::create(dac::OpKind::Add);
    auto e2=dac::Entry::create(dac::OpKind::Add);
    auto o1=dac::DacOperand::createResult(e1);
    auto o2=dac::DacOperand::createResult(e1);
    auto o3=dac::DacOperand::createResult(e2);
    REQUIRE(Compare_operand_pointer<std::equal_to<void*>>(o1,o1));
    REQUIRE(Compare_operand_pointer<std::equal_to<void*>>(o1,o2));
    REQUIRE_FALSE(Compare_operand_pointer<std::equal_to<void*>>(o1,o3));
    REQUIRE_FALSE(Compare_operand_pointer<std::equal_to<void*>>(o2,o3));
}