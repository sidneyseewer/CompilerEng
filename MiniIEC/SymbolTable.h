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
