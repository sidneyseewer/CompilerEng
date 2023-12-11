#include "SymbolTable.h"
#include <exception>

    // Method to add a symbol to the table
    void SymbolTable::Add(Symbol::ptr symbol) {
        symbols[symbol->GetName()] = symbol;
    }

    // Method to find a symbol in the table
    Symbol::ptr SymbolTable::Find(const std::string& name) {
        if(symbols.contains(name))
        {
            return symbols[name];
        }
                    return nullptr;
        
    }
