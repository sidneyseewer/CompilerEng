#ifndef __TYPE_H__
#define __TYPE_H__

#include <cstddef>
#include <memory>
class Symbol;
class Type {
public:
  using ptr=std::shared_ptr<Type>;
  virtual std::size_t getSize() = 0;
  // virtual Symbol getName(Symbol s) {return s.getName();};
};

#endif