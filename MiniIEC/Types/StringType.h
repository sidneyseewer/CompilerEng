#ifndef __STRING_TYPE_H__
#define __STRING_TYPE_H__

#include "Types/Type.h"
#include <cstddef>
class StringType : public Type {
  size_t mLength;
  public:
    static StringType::ptr create( ){return std::make_shared<StringType>();}
};

#endif //!__STRING_TYPE_H__