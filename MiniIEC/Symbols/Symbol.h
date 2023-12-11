#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "../Types/Type.h"
#include <memory>
#include <string>
class Symbol {
private:
  std::string mNmae;
  Type::ptr mType;

protected:
  Symbol(std::string name,Type::ptr type) : mNmae(name),mType(type) {}

public:
  using ptr = std::shared_ptr<Symbol>;
  std::string GetName() const { return mNmae; };
  Type::ptr getType() const { return mType; };
};
#endif