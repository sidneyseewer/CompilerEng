#ifndef __TYPE_H__
#define __TYPE_H__

#include <cstddef>
class Symbol;
class Type {
public:
  virtual std::size_t getSize() = 0;
  virtual Symbol getName() = 0;
};

#endif