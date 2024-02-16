#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "../Types/Type.h"
#include <memory>
#include <string>
#include "../lib/concepts.h"
class Symbol {
private:
  std::string mNmae;
  Type::ptr mType;

protected:
  Symbol(std::string name,Type::ptr type) : mNmae(name),mType(type) {}

public:
  using ptr = std::shared_ptr<Symbol>;
  virtual std::string GetName() const { return mNmae; };
  virtual Type::ptr getType() const { return mType; };
};
template <Derived<Symbol> F>
F* extract(std::shared_ptr<Symbol>o){
    if(o!=nullptr) return dynamic_cast<F*>(o.get());return nullptr;
}

#endif