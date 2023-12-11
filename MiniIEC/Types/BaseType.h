#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
class BaseType : public Type {
  const TypeKind mKind;
  const size_t msize;
  Symbol::ptr mSymbol;

public:
  using ptr = std::shared_ptr<BaseType>;
  static BaseType::ptr create(TypeKind kind, size_t size) {
    return std::make_shared<BaseType>(kind, size);
  }
  BaseType(TypeKind kind, size_t size) : mKind(kind), msize(size) {}
  void setSymbol(Symbol::ptr s) { mSymbol = s; }
  std::size_t getSize() const override { return msize; }
  Symbol::ptr getName() const override { return mSymbol; }
};

#endif //!__BASE_TYPE_H__