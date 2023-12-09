// symboltable.h
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <string>

enum class DataType {
    INT,
    FLOAT,
    CHAR,
    // Add more data types as needed
};

struct SymbolEntry {
    DataType dataType;
    int offset; // Example: offset within the memory
    // Add more information as needed

//    SymbolEntry(DataType type, int off) : dataType(type), offset(off) {}
};

class SymbolTable {
public:
    SymbolTable();

    void insert(const std::string& identifier, DataType dataType, int offset);
    bool lookup(const std::string& identifier, SymbolEntry& entry) const;

private:
    std::unordered_map<std::string, SymbolEntry> symbolMap;
};

#endif // SYMBOLTABLE_H
