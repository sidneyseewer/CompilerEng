// test.cpp
#include "SymbolTable.h"
#include <iostream>

int testSymbolTable() {
    // Get the singleton instance of the SymbolTable
    SymbolTable& symbolTable = SymbolTable::GetInstance();

    // Insert entries into the symbol table
    // symbolTable.insert("variable1", DataType::INT);
    // symbolTable.insert("variable2", DataType::INT);
    // symbolTable.insert("variable3", DataType::INT);

    // // Look up entries in the symbol table
    // SymbolEntry entry;
    // if (symbolTable.lookup("variable1", entry)) {
    //     std::cout << "Found entry for variable1:" << std::endl;
    // }
    // else {
    //     std::cout << "Entry for variable1 not found" << std::endl;
    // }

    // if (symbolTable.lookup("variable2", entry)) {
    //     std::cout << "Found entry for variable2:" << std::endl;
    // }
    // else {
    //     std::cout << "Entry for variable2 not found" << std::endl;
    // }

    // if (symbolTable.lookup("variable3", entry)) {
    //     std::cout << "Found entry for variable3:" << std::endl;
    // }
    // else {
    //     std::cout << "Entry for variable3 not found" << std::endl;
    // }

    return 0;
}
