#ifndef ___VAR_SYMBOL_H__
#define ___VAR_SYMBOL_H__

#include "Symbols/Symbol.h"
#include <cstddef>
class VarSymbol: public Symbol
{
    size_t mOffset;
    public:
    size_t getOffset();
};

#endif //!__VAR_SYMBOL_H_