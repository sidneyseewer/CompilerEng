#ifndef __ARRAY_TYPE_H__
#define __ARRAY_TYPE_H__

#include "Types/Type.h"
class ArrayType : public Type {
  Type mElementType;

public:
  ArrayType(Type t) : mElementType(t) {}
};

#endif //!__ARRAY_TYPE_H__