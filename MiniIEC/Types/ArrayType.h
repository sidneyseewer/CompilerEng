#ifndef __ARRAY_TYPE_H__
#define __ARRAY_TYPE_H__

#include "Types/Type.h"
class ArrayType : public Type {
  Type::ptr mElementType;

public:
    static ArrayType::ptr create(Type::ptr type){return std::make_shared<ArrayType>(type);}
  ArrayType(Type::ptr t) : mElementType(t) {}
};

#endif //!__ARRAY_TYPE_H__