#ifndef __STRING_TYPE_H__
#define __STRING_TYPE_H__

#include "Types/Type.h"
#include <cstddef>
#include <pthread.h>


class StringType : public Type {
  size_t mLength;

  public:
    static StringType::ptr create(){return std::make_shared<StringType>();}
    StringType():mLength(1){}
   std::size_t getSize() const override{return mLength;}
};

#endif //!__STRING_TYPE_H__