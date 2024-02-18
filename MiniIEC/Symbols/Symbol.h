#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "../Types/Type.h"
#include "../lib/concepts.h"
#include <memory>
#include <string>
class Symbol {
private:
  std::string mNmae;
  Type::ptr mType;

protected:
  Symbol(std::string const &name, Type::ptr const &type);

public:
  using ptr = std::shared_ptr<Symbol>;
  virtual std::string GetName() const;
  virtual Type::ptr getType() const;
};

template <Derived<Symbol> F> F *extract(std::shared_ptr<Symbol> const &o) {
  if (o != nullptr)
    return dynamic_cast<F *>(o.get());
  return nullptr;
}

#endif