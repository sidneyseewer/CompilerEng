#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
class BaseType : public Type {
    TypeKind mKind;
    public:
    BaseType(TypeKind kind,size_t size):mKind(kind){}
    std::size_t getSize(){return 5;};
};

#endif //!__BASE_TYPE_H__