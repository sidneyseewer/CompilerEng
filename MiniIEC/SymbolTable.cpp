// symboltable.cpp
#include "symboltable.h"

SymbolTable SymbolTable::instance; // Initializing static instance

SymbolTable::SymbolTable() : currentOffset(0) {}

SymbolTable& SymbolTable::getInstance() {
    return instance;
}

void SymbolTable::insert(const std::string& identifier, DataType dataType) {
    SymbolEntry entry;
    entry.dataType = dataType;
    currentOffset += 4; // Increment offset for the next entry
    symbolMap[identifier] = entry;
}

bool SymbolTable::lookup(const std::string& identifier, SymbolEntry& entry) const {
    auto it = symbolMap.find(identifier);
    if (it != symbolMap.end()) {
        entry = it->second;
        return true;
    }
    return false;
}
