#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include "Symbols/Symbol.h"
#include "Symbols/TypeSymbol.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
class BaseType : public Type {
public:
  using ptr = std::shared_ptr<BaseType>;

private:
  const TypeKind mKind;
  const size_t msize;
  Symbol::ptr mSymbol;

public:
  BaseType(TypeKind const &kind, size_t const &size);
  static BaseType::ptr create(TypeKind const &kind, size_t const &size) {
    return std::make_shared<BaseType>(kind, size);
  }
  void setSymbol(Symbol::ptr const &s);
  std::size_t getSize() const override;
  Symbol::ptr getName() const override;
};

#endif //!__BASE_TYPE_H__