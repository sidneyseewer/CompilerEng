#pragma once
#include "Symbols/Symbol.h"
#include "lib/Singelton.h"
#include <string>
#include <unordered_map>

class Parser;
class Errors;


// Singleton class SymbolTable
class SymbolTable:public Singelton<SymbolTable> {
public:
    // Method to add a symbol to the table
    void Add(Symbol::ptr symbol);

    // Method to find a symbol in the table
    Symbol::ptr Find(const std::string& name);


private:
    friend class Singelton<SymbolTable>;
    // Private constructor to enforce singleton pattern
    std::unordered_map<std::string, Symbol::ptr> symbols{{"integer",nullptr}};
};