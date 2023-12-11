#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include "Types/Type.h"
#include "Types/TypeKind.h"
#include <cstddef>
#include <memory>
class BaseType : public Type {
    TypeKind mKind;
    size_t msize;
    public:
    static BaseType::ptr create(TypeKind kind,size_t size){return std::make_shared<BaseType>(kind,size);}
    BaseType(TypeKind kind,size_t size):mKind(kind),msize(size){}
    size_t getSize()const{return msize;}
};

#endif //!__BASE_TYPE_H__