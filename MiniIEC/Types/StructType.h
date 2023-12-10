#ifndef __STRUCT_TYPE_H__
#define __STRUCT_TYPE_H__

#include "Symbols/VarSymbol.h"
#include "Types/Type.h"
#include <vector>
class StructType : public Type {
  std::vector<VarSymbol> mEbus;
  public:

    static StructType::ptr create(){return std::make_shared<StructType>();}
};

#endif //!__STRUCT_TYPE_H__