#ifndef __STRUCT_TYPE_H__
#define __STRUCT_TYPE_H__

#include "Symbols/VarSymbol.h"
#include "Types/Type.h"
#include <vector>
class StructType : public Type {
  std::vector<VarSymbol> mEbus;
};

#endif //!__STRUCT_TYPE_H__