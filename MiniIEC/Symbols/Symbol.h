#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include <memory>
#include <string>
#include "../Types/Type.h"
class Symbol{
private:
    std::string mNmae;
public:
using ptr=std::shared_ptr<Symbol>;
    Symbol(std::string name):mNmae(name){}
    std::string GetName(){return mNmae;};
    virtual Type::ptr getType()=0;
};
#endif