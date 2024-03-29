/**
 * @file CodeGenAdapter.cpp
 * @author Florian Gapp, Sidney Seewer  ()
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "CodeGenAdapter.h"
#include "dac/Operands/SymbolOperand.h"
CodeGenAdapter::CodeGenAdapter(CodeGen<int32_t> *pgen, bool const& dryRun)
    : dryRun(dryRun), gen(pgen) {}
void CodeGenAdapter::Run(std::vector<dac::Entry::ptr> const &g) {
  if(gen==nullptr) throw "nullpointer";

  RegisterAdmin regadm{gen->GetRegCnt()};
  auto temRegInstruction = dac::Entry::create(dac::OpKind::Exit);
  auto tempReg = regadm.GetRegister();
  regadm.AssignRegister(tempReg, temRegInstruction);

  RegisterAdmin::RegNr ra = 0;
  RegisterAdmin::RegNr rb = 0;
  RegisterAdmin::RegNr rc = 0;
  for (size_t i = 0; i < g.size(); i++) {
    dac::Entry::ptr e = *(g.begin() + i);
    size_t jumpDestination;
    dac::SymbolOperand *f1s{nullptr};
    dac::SymbolOperand *f2s;
    dac::DacOperand *f1d;
    dac::DacOperand *f2d;
    f1s = dac::extract<dac::SymbolOperand>(e->getFirst());
    f1d = dac::extract<dac::DacOperand>(e->getFirst());
    f2s = dac::extract<dac::SymbolOperand>(e->getSecond());
    f2d = dac::extract<dac::DacOperand>(e->getSecond());
    auto x = dac::DacOperand::createResult(e);
    if (e->isJumpDestination) {
      regadm.FreeRegister(ra);
      regadm.FreeRegister(rb);
      // regadm.FreeRegister(rc);
    }
    if (dryRun) {
      e->setPosition(gen->GetCodePosition());
    } else {
      assert(e->getPosition() == gen->GetCodePosition());
    }
    switch (e->getKind()) {

    case dac::Add:
    case dac::Sub:
    case dac::Mult:
    case dac::Div:
      // create result

      if (regadm.hasRegister(x)) {
        rc = regadm.GetRegister(x);
      } else {
        rc = regadm.AssignRegister(regadm.GetRegister(), e);
      }

    case dac::IsEq:
    case dac::IsLeq:
    case dac::IsGtq:
    case dac::IsNotEq:
    case dac::IsLess:
    case dac::IsGreater:
      // create ra,rb
      // create ra
      if (f1s != nullptr) {
        if (regadm.hasRegister(e->getFirst())) {
          ra = regadm.GetRegister(e->getFirst());
        } else {
          ra = regadm.AssignRegister(regadm.GetRegister(), f1s->get());
          auto constsym = extract<ConstSymbol>(f1s->get());
          auto varsym = extract<VarSymbol>(f1s->get());
          if (constsym != nullptr)
            gen->LoadI(ra, constsym->getValue());
          if (varsym != nullptr)
            gen->Load(ra, 0, varsym->getOffset());
        }
      } else if (f1d != nullptr) {
        if (regadm.hasRegister(e->getFirst())) {
          ra = regadm.GetRegister(e->getFirst());
        } else {
          throw "required value does not exist";
        }
      }

    case dac::Print:
    case dac::Assign:
      // create rb
      if (f2s != nullptr) {
        if (regadm.hasRegister(e->getSecond())) {
          rb = regadm.GetRegister(e->getSecond());
        } else {
          rb = regadm.AssignRegister(regadm.GetRegister(), f2s->get());
          auto constsym = extract<ConstSymbol>(f2s->get());
          auto varsym = extract<VarSymbol>(f2s->get());
          if (constsym != nullptr)
            gen->LoadI(rb, constsym->getValue());
          if (varsym != nullptr)
            gen->Load(rb, 0, varsym->getOffset());
        }
      } else if (f2d != nullptr) {
        if (regadm.hasRegister(e->getSecond())) {
          rb = regadm.GetRegister(e->getSecond());
        } else {
          throw "required value does not exist";
        }
      }
      break;
    case dac::Jump:
    case dac::IfFalse:
    case dac::Exit:
      break;
    }
    switch (e->getKind()) {
    case dac::IsEq:
    case dac::IsLeq:
    case dac::IsGtq:
    case dac::IsNotEq:
    case dac::IsLess:
    case dac::IsGreater:
      i++;
      if (dryRun) {
        (g.begin() + i)->get()->setPosition(e->getPosition());
      } else {
        assert(e->getPosition() == (g.begin() + i)->get()->getPosition());
      }
    case dac::Jump: {
      auto j = *(g.begin() + i);
      dac::DacOperand *x;
      if (j->getSecond() != nullptr) {
        x = extract<dac::DacOperand>(j->getSecond());
      } else {
        x = extract<dac::DacOperand>(j->getFirst());
      }
      jumpDestination = x->getJump()->getPosition();
#ifndef NDEBUG
      // std::cout << dac::OpKindToString(e->getKind()) << ":" << jumpDestination
      //           << std::endl;
#endif
    }

    break;

    case dac::Add:
    case dac::Sub:
    case dac::Mult:
    case dac::Div:
    case dac::Assign:
    case dac::IfFalse:
    case dac::Print:
    case dac::Exit:
      break;
    }
    switch (e->getKind()) {

    case dac::Add:
      gen->Add(ra, rb, rc);
      break;
    case dac::Sub:
      gen->Sub(ra, rb, rc);
      break;
    case dac::Mult:
      gen->Mul(ra, rb, rc, tempReg);
      break;
    case dac::Div:
      gen->Div(ra, rb, rc, tempReg, tempReg, tempReg);
      // TODO:
      break;
    case dac::IfFalse:
      break;

    case dac::Assign:
      // gen->LoadI(ra, extract<VarSymbol>(f1s->get())->getOffset());
      gen->Store(rb, 0, extract<VarSymbol>(f1s->get())->getOffset());
      // std::cout<<"";
      break;
    case dac::Jump:
      gen->JumpEQ(0, 0, tempReg, jumpDestination);
      break;
      break;
    case dac::Print:
      gen->PrintInt(rb);
      break;
    case dac::Exit:
      gen->Sleep();
      break;
    case dac::IsEq:
      // jumps.emplace_back(Args &&args...)
      gen->JumpNEQ(ra, rb, tempReg, jumpDestination);
      break;
    case dac::IsLeq:
      gen->JumpG(ra, rb, tempReg, jumpDestination);
      break;
    case dac::IsGtq:
      gen->JumpLE(ra, rb, tempReg, jumpDestination);
      break;
    case dac::IsNotEq:
      gen->JumpEQ(ra, rb, tempReg, jumpDestination);
      break;
    case dac::IsLess:
      gen->JumpGE(ra, rb, tempReg, jumpDestination);
      break;
    case dac::IsGreater:
      gen->JumpLE(ra, rb, tempReg, jumpDestination);
      break;
      break;
    }
    if (!e->hasNextUse(e->getFirst()) && ra != 0) {
      regadm.FreeRegister(ra);
    }

    if (!e->hasNextUse(e->getSecond()) && rb != 0) {
      regadm.FreeRegister(rb);
    }
    if (!e->hasNextUse(dac::DacOperand::createResult(e)) && rc != 0) {
      regadm.FreeRegister(rc);
    }
  }
}