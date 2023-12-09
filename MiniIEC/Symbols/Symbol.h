#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include <string>
#include "../Types/Type.h"
class Symbol{
private:
    std::string mNmae;
public:
    virtual std::string GetName()=0;
    virtual Type getType()=0;
};
#endif