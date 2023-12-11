#ifndef __STRUCT_TYPE_H__
#define __STRUCT_TYPE_H__

#include "Symbols/VarSymbol.h"
#include "Types/Type.h"
#include <cstddef>
#include <numeric>
#include <vector>
class StructType : public Type {
  std::vector<VarSymbol> mElemts;
  public:
    static StructType::ptr create(){return std::make_shared<StructType>();}
    size_t getSize(){return std::accumulate(mElemts.cbegin(),mElemts.cend(),0,[](size_t p,VarSymbol const& t){return  t.getType()->getSize();});}
};

#endif //!__STRUCT_TYPE_H__