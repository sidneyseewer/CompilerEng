#ifndef __TYPE_H__
#define __TYPE_H__

#include <cstddef>
#include <memory>

class Symbol;
class Type {
public:
  using ptr = std::shared_ptr<Type>;
  virtual std::size_t getSize() const = 0;
  virtual std::shared_ptr<Symbol> getName() const = 0;
};

#endif