
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
    using container=std::unordered_map<std::string, Symbol::ptr>;
    container::const_iterator cbegin()const{return symbols.cbegin();}
    container::const_iterator cend()const{return symbols.cend();}
private:
    friend class Singelton<SymbolTable>;
    // Private constructor to enforce singleton pattern
    int currentOffset; // Member to track current offset

    container symbols;
};

#endif //!SYMBOLTABLE_H
