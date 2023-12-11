#include "SymbolTable.h"
#include "Types/Type.h"
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
void SymbolTable::insert(const std::string& identifier, Symbol::ptr dataType) {
    currentOffset += 4; // Increment offset for the next entry
    symbols[identifier] = dataType;
}

bool SymbolTable::lookup(const std::string& identifier, Symbol::ptr entry) const {
    auto it = symbols.find(identifier);
    if (it != symbols.end()) {
        entry = it->second;
        return true;
    }
    return false;
}