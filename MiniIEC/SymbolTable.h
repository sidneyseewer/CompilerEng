
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

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
void insert(const std::string& identifier, Symbol::ptr dataType);
bool lookup(const std::string& identifier, Symbol::ptr entry) const;

private:
    friend class Singelton<SymbolTable>;
    // Private constructor to enforce singleton pattern
    int currentOffset; // Member to track current offset

    std::unordered_map<std::string, Symbol::ptr> symbols;
};

#endif //!SYMBOLTABLE_H
