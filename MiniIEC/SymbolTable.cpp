#include "SymbolTable.h"

    // Method to add a symbol to the table
    void SymbolTable::Add(Symbol* symbol) {
        symbols[symbol->GetName()] = symbol;
    }

    // Method to find a symbol in the table
    Symbol* SymbolTable::Find(const std::string& name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Method to get the singleton instance of SymbolTable
    SymbolTable& SymbolTable::GetInstance() {
        static SymbolTable instance;
        return instance;
    }

    // Method to delete the singleton instance of SymbolTable
    void SymbolTable::DeleteInstance() {
        SymbolTable& instance = GetInstance();
        delete& instance;
    }


    // Destructor to clean up resources
    SymbolTable::~SymbolTable() {
        for (auto& entry : symbols) {
            delete entry.second;
        }
        symbols.clear();
    }

    // Private copy constructor and assignment operator to prevent copying

    // std::unordered_map<std::string, Symbol*> symbols;