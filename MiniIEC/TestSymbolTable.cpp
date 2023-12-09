// test_symboltable.cpp
#include "symboltable.h"

int testSymbolTable() {
    SymbolTable symbolTable;

    // Test insert and lookup
    symbolTable.insert("variable1", DataType::INT, 0);
    symbolTable.insert("variable2", DataType::FLOAT, 4);

    SymbolEntry entry;
    if (symbolTable.lookup("variable1", entry)) {
        std::cout << "Found variable1 in the symbol table. Type: " << static_cast<int>(entry.dataType) << "\n";
    }
    else {
        std::cout << "Variable1 not found in the symbol table.\n";
    }

    if (symbolTable.lookup("variable3", entry)) {
        std::cout << "Found variable3 in the symbol table. Type: " << static_cast<int>(entry.dataType) << "\n";
    }
    else {
        std::cout << "Variable3 not found in the symbol table.\n";
    }

    return 0;
}
