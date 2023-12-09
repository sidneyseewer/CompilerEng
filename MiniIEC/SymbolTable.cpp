// symboltable.cpp
#include "symboltable.h"

SymbolTable::SymbolTable() {}

void SymbolTable::insert(const std::string& identifier, DataType dataType, int offset) {
    SymbolEntry entry;
    entry.dataType = dataType;
    entry.offset = offset;
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
