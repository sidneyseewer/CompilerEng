<<<<<<< HEAD
// symboltable.h
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <string>

enum class DataType {
    INT,
};

struct SymbolEntry {
    DataType dataType;
};

class SymbolTable {
public:
    static SymbolTable& getInstance();

    void insert(const std::string& identifier, DataType dataType);
    bool lookup(const std::string& identifier, SymbolEntry& entry) const;

private:
    SymbolTable(); // Private constructor for Singleton

    std::unordered_map<std::string, SymbolEntry> symbolMap;
    int currentOffset; // Member to track current offset

    static SymbolTable instance; // Static instance for Singleton
};

#endif // SYMBOLTABLE_H
=======
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
>>>>>>> efe0d13cc5969fab985cf05da968372d3b1cea05
