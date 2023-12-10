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
    void Add(Symbol* symbol);

    // Method to find a symbol in the table
    Symbol* Find(const std::string& name);

    // Method to get the singleton instance of SymbolTable
    static SymbolTable& GetInstance();

    // Method to delete the singleton instance of SymbolTable
    static void DeleteInstance();

private:
    // Private constructor to enforce singleton pattern
    SymbolTable() {}

    // Destructor to clean up resources
    ~SymbolTable();

    // Private copy constructor and assignment operator to prevent copying
    SymbolTable(const SymbolTable&) = delete;
    SymbolTable& operator=(const SymbolTable&) = delete;

    std::unordered_map<std::string, Symbol*> symbols;
};